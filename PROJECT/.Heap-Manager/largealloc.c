#include <stdio.h>
#include "largealloc.h"
#include <limits.h>
#include <error.h>

large_alloc_list largeAllocList;
// initializes largealloclist when called first time
void LargeAllocInit()
{
    for (int i = 0; i < MAX_SIZE_FOR_LARGE_ALLOC; i++)
    {
        largeAllocList.largeBlock[i].ptr = NULL;
        largeAllocList.largeBlock[i].offset = 0;
        largeAllocList.largeBlock[i].remainingSize = 0;
    }
    return;
}
// split blocks into two parts in a such a way that one part has memory equal to
// memory requested. splits teh blocks only when it will not result into hard fragmentation
int splitLargeBlock(mdb mptr, size_t bytes)
{
    if (mptr->blockSize <= bytes)
        return INT_MIN;

    mdb temp = NULL, next = NULL, ptr = NULL;

    if (mptr->nextBlock)
        ptr = mptr->nextBlock->nextBlock;
    else
        ptr = NULL;

    size_t size = mptr->blockSize;
    temp = mptr;
    temp->blockSize = bytes;
    temp->nextBlock = (mdb)(((char *)temp) + METABLOCK_SIZE + bytes);
    next = temp->nextBlock;
    next->prevBlock = temp;
    next->nextBlock = ptr;
    next->blockSize = (size - (bytes + METABLOCK_SIZE));
    next->isFree = TRUE;
    next->headPtr = temp->headPtr;
    return 1;
}
// merge two consecutive memory block together to form a single block.
// called by FREE() when two consecutive blocks are unused.
int mergeLargeBlock(mdb m)
{
    if (!m | !m->nextBlock || m->isFree == FALSE || m->nextBlock->isFree == FALSE)
        return INT_MIN;
    mdb a;
    a = m->nextBlock;
    size_t nextSize = a->blockSize;
    m->nextBlock = a->nextBlock;
    a->nextBlock->prevBlock = m;
    m->blockSize += METABLOCK_SIZE + nextSize;
    return 1;
}

// returns pointer to the memory block that has size greater than or equal to
// the size available in the page. if no block available then new block is allocated
// by allocating new page.
void *returnLargeBlock(size_t bytes)
{
    int i = 0, requiresPages;
    while (i <= largeAllocList.count && bytes <= largeAllocList.largeBlock[i].remainingSize)
        i++;
    if (i >= largeAllocList.count && !largeAllocList.largeBlock[0].ptr && largeAllocList.largeBlock[0].remainingSize == 0 && largeAllocList.largeBlock[0].offset == 0)
    {
        // if largeAllocList is empty then new page is allocating according to the requirement
        requiresPages = 4 > ((bytes + METABLOCK_SIZE) / SYS_PG_SZ) ? 4 : ((bytes + METABLOCK_SIZE) / SYS_PG_SZ) + 1;
        largeAllocList.largeBlock[0].ptr = (mdb)getPages(requiresPages);
        largeAllocList.largeBlock[0].offset = 0;
        largeAllocList.largeBlock[0].remainingSize = bytes;
        largeAllocList.count = 0;
        mdb temp;
        temp = largeAllocList.largeBlock[0].ptr;
        temp->blockSize = bytes;
        temp->prevBlock = NULL;
        temp->nextBlock = NULL;
        temp->isFree = TRUE;
        temp->headPtr = temp;
        i = 0;
    }
    if (i <= largeAllocList.count)
    {
        // memory block with required size is available
        mdb mptr;
        mptr = largeAllocList.largeBlock[i].ptr;
        while (mptr->blockSize < bytes)
            mptr = mptr->nextBlock;
        mptr->headPtr = largeAllocList.largeBlock[i].ptr;
        int buf = mptr->blockSize % bytes;
        if (buf < (METABLOCK_SIZE + 1024))
            return (void *)(mptr + 1);
        else
        {
            // splitting the block of memory only if it does not result into hard
            // fragmentation
            if (splitLargeBlock(mptr, bytes) == INT_MIN)
                return NULL;
            else
                return (void *)(mptr + 1);
        }
    }
    else
    {
        // no block of memory satisfy the request so allocate a new page
        largeAllocList.count += 1;
        if (largeAllocList.count >= MAX_SIZE_FOR_LARGE_ALLOC)
            return NULL;

        requiresPages = 4 > ((bytes + METABLOCK_SIZE) / SYS_PG_SZ) ? 4 : (bytes + METABLOCK_SIZE) / SYS_PG_SZ;
        largeAllocList.largeBlock[largeAllocList.count].ptr = (mdb)getPages(requiresPages);
        largeAllocList.largeBlock[largeAllocList.count].offset = 0;
        largeAllocList.largeBlock[largeAllocList.count].remainingSize = requiresPages * SYS_PG_SZ - METABLOCK_SIZE;
        mdb temp, a;
        temp = largeAllocList.largeBlock[largeAllocList.count].ptr;
        temp->blockSize = bytes;
        temp->prevBlock = NULL;
        temp->nextBlock = (mdb)((char *)temp + bytes + METABLOCK_SIZE);
        temp->isFree = FALSE;
        temp->headPtr = temp;

        largeAllocList.largeBlock[largeAllocList.count].remainingSize -= (bytes + METABLOCK_SIZE);
        largeAllocList.largeBlock[largeAllocList.count].offset = METABLOCK_SIZE + bytes;

        a = temp->nextBlock;
        a->prevBlock = temp;
        a->nextBlock = NULL;
        a->blockSize = largeAllocList.largeBlock[largeAllocList.count].remainingSize;
        a->isFree = TRUE;
        a->headPtr;
        return (void *)(temp + 1);
    }
}

// to find whether the large allocated page is empty or not.
// return TRUE if all the blocks are free and returns FALSE if there is atleast one block which is not in use.
int isLargeAllocPageEmpty(mdb head)
{
    mdb ptr = head;
    while (ptr)
    {
        if (ptr->isFree == FALSE)
            return FALSE;
        ptr = ptr->nextBlock;
    }
    return TRUE;
}
// unmaps the pages if they are empty, this function is called by FREE()
// when it detect that whole page is empty
void removeLargeAllocPage(mdb head)
{
    int i = 0;
    while (i < MAX_SIZE_FOR_LARGE_ALLOC && head != largeAllocList.largeBlock[i].ptr)
        i++;
    if (i == MAX_SIZE_FOR_LARGE_ALLOC)
        return;
    large_alloc temp = largeAllocList.largeBlock[i];
    largeAllocList.largeBlock[i] = largeAllocList.largeBlock[largeAllocList.count];
    largeAllocList.largeBlock[largeAllocList.count].offset = 0;
    largeAllocList.largeBlock[largeAllocList.count].remainingSize = 0;
    largeAllocList.largeBlock[largeAllocList.count].ptr = NULL;
    largeAllocList.count -= 1;
    freePages(head, 4);

    return;
}