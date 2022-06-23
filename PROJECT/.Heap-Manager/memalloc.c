#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <stdint-gcc.h>
#include <limits.h>
#include "memalloc.h"
#include "sizeclasses.h"
#include "freelist.h"
#include "sizeclassfreelist.h"
#include "largealloc.h"

size_t SYS_PG_SZ = 0;
// Wrapper function to mmap() system call.
// Returns Address of the virtual memory pages that are allocated. Returns NULL if mapping is failed

void *getPages(int n)
{
    char *vmPage = mmap(NULL, n * SYS_PG_SZ, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
    if (vmPage == MAP_FAILED)
    {
        perror("Error! Virtual memory page allocation failed.\n");
        return NULL;
    }
    memset(vmPage, 0, n * SYS_PG_SZ);
    return (void *)vmPage;
}
// Wrapper function to munmap() system call
// Returns the memory pages back to the kernel ( frees the page)
void freePages(void *vmPage, int n)
{
    if (munmap(vmPage, n * SYS_PG_SZ))
        perror("Error! Cannot unmap virtual memory page to kernel\n");
}
//  returns unused memory block from a virtual memory page
mdb getFreeBlock(mdb head) {

    mdb a;
    a= head;
    while(a->nextBlock && a->isFree == FALSE) {
        a = a->nextBlock;
    }
    return a;
    
}
// used for dynamic allocation of memory. returns pointer to the requested amount of memory
void *MALLOC(size_t bytes)
{
    static int isInit = FALSE;
// initializing the size-classes and free-lists
    if (isInit == FALSE)
    {
        SYS_PG_SZ = getpagesize();
        initSizeClassList();
        LargeAllocInit();
        initSizeClassFreeList();
        initFreeList(&freeList);
        isInit = TRUE;
    }
    if (bytes <= 0)
        return NULL;
    // memory requirement is less than 1KB (for size-classes)
    if (bytes < CLASS_SIZE_LIMIT)
    {
        int sizeclass = 0;
        while (bytes > classSizeArray[sizeclass])
            sizeclass++;
    // if freed blocks are available in freeList return 
        if (isSizeClassFreeListEmpty(sizeclass) == FALSE)
            return (void *)(getFreeBlockFromFreeList(bytes) + 1);

        int i = 0;
        while (bytes > classSizeArray[i])
            i++;

        mdb ptr, mptr;
    // getting page from the sizeClassList which has atleast one block available for use
        ptr = getPageForAllocation(i);
        int k = 0;
        while (k < MAX_PAGES && sizeClassList[i][k].head != ptr)
            k++;
        if (!ptr)
            return NULL;

        mptr = getFreeBlock(ptr);
        mptr->isFree = FALSE;
        mptr->headPtr = ptr;
        return (void *)(mptr + 1);
    }
    else
    {
        // if memory requirement is greater than 1 Kb (large allocation)
        // checking if the memory block is available in the free list
        // sorting the heap of free list containing the poitner to memory blocks
        sortFreeList(&freeList);
        int i = 0;
        while (i <= freeList.rear && bytes > freeList.list[i].blockSize)
            i++;
        if (i <= freeList.rear)
        {
            mdb bptr;
            // splitting the memory block only if the remaining block will not cause hard
            // memory fragmentation
            if (freeList.list[i].blockSize > (bytes + METABLOCK_SIZE + CLASS_SIZE_LIMIT))
            {
                if (splitLargeBlock(freeList.list[i].blockPtr, freeList.list[i].blockSize) == INT_MIN)
                    return NULL;
                addBlockToFreeList(&freeList, freeList.list[i].blockPtr->nextBlock);
                bptr = freeList.list[i].blockPtr;
                deleteBlockFromFreeList(&freeList, freeList.list[i].blockSize, freeList.list[i].blockPtr);
                return (void *)(bptr + 1);
            }
            bptr = freeList.list[i].blockPtr;
            deleteBlockFromFreeList(&freeList, freeList.list[i].blockSize, freeList.list[i].blockPtr);
            return (void *)(bptr + 1);
        }
        // if free-list do not contain any block, allocating new block in memory page
        else
        {
            return returnLargeBlock(bytes);
        }
    }
    return NULL;
}
// function to free the dynamically allocated memory 
void FREE(void *ptr)
{
    mdb mptr;
    mptr = (mdb)ptr - 1;
    if (!mptr)
        return;
    if (mptr->isFree == TRUE)
        return;

    if (mptr->blockSize < CLASS_SIZE_LIMIT)
    {
        mdb headptr;
        headptr = mptr->headPtr;
        int sizeClass = 0;
        while (sizeClass < NUM_OF_CLASSES && mptr->blockSize > classSizeArray[sizeClass])
            sizeClass++;

        static int isInit = FALSE;

        if (isInit == FALSE)
        {
            initSizeClassFreeList();
            isInit = TRUE;
        }

        int offset = 0;
        while (offset < MAX_PAGES && headptr != sizeClassList[sizeClass][offset].head)
            offset++;
        mptr->isFree = TRUE;
        if (isSizeClassPageEmpty(sizeClass, offset) == TRUE)
        {
            // if complete memory page is empty then unmap it to th kernel
            removeAllFreeListBlocksFromOffset(sizeClass, offset);
            removeEmptySizeClassPage(sizeClass, offset);
            return;
        }
        else
            addBlockToSizeClassFreeList(mptr, mptr->blockSize, offset);
    }
    else
    {
        // memory block belongs to large alloc
        mdb next = mptr->nextBlock;
        mdb prev = mptr->prevBlock;
        mdb head;
        // merging next and prev memory blocks if they are free
        if (next->isFree == TRUE)
            mergeLargeBlock(mptr);
        if (prev->isFree == TRUE)
        {
            mergeLargeBlock(prev);
            if (isLargeAllocPageEmpty(prev->headPtr) == TRUE)
            {
                // return page to the kernel if all blocks are free
                head = prev->headPtr;
                for (int i = 0; i <= freeList.rear; i++)
                {
                    if (freeList.list[i].blockPtr->headPtr == head)
                        deleteBlockFromFreeList(&freeList, freeList.list[i].blockSize, freeList.list[i].blockPtr);
                }
                removeLargeAllocPage(head);
            }
            else
                addBlockToFreeList(&freeList, prev);
        }
        else
        {
            if (isLargeAllocPageEmpty(mptr->headPtr) == TRUE)
            {
                head = mptr->headPtr;
                for (int i = 0; i <= freeList.rear; i++)
                {
                    if (freeList.list[i].blockPtr->headPtr == head)
                        deleteBlockFromFreeList(&freeList, freeList.list[i].blockSize, freeList.list[i].blockPtr);
                }
                removeLargeAllocPage(head);
            }
            else
                addBlockToFreeList(&freeList, mptr);
        }
    }
    return;
}
// dynamically allocates memory and initializes it to zero 

void *CALLOC(size_t num, size_t size)
{
    void *ptr;

    ptr = MALLOC(num * size);
    if (!ptr)
        return NULL;
    // initializing it to zero
    bzero(ptr, num * size);
    return ptr;
}

// reallocates the dynamically allocated memory to a new size.
// free the intial memory if size is zero.
void *REALLOC(void *ptr, size_t size)
{
    mdb mptr;
    if (!ptr)
        return MALLOC(size);
    mptr = (((mdb)ptr) - 1);
    if (size < 0)
        return NULL;
    if (size == 0)
    {
        FREE(ptr);
        return NULL;
    }
    void *newPtr;
    newPtr = MALLOC(size);
    if (!newPtr)
        return NULL;
// Moving contents to the memory to the new allocated location
    if (mptr->blockSize < size)
        memmove(newPtr, ptr, mptr->blockSize);
    else
        memmove(newPtr, ptr, size);
    FREE(ptr);
    return newPtr;
}