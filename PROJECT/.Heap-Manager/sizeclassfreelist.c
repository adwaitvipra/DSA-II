#include <stdio.h>
#include "sizeclassfreelist.h"

sizeClass_free_list sizeClassFreeList[NUM_OF_CLASSES];

// initializes the sizefree classList when it is called for the firt time
void initSizeClassFreeList()
{
    for (int i = 0; i < NUM_OF_CLASSES; i++)
    {
        for (int j = 0; j < SIZECLASS_FREE_LIST_SIZE; j++)
        {
            sizeClassFreeList[i].l[j].blockPtr = NULL;
            sizeClassFreeList[i].l[j].blockSize = 0;
            sizeClassFreeList[i].l[j].offset = -1;
        }
        sizeClassFreeList[i].rear = -1;
    }
}

// to find wheter the free-list is empty for a particular size-class
// return TRUE if empty and vice-versa
int isSizeClassFreeEmpty(int sizeclass)
{
    for (int j = 0; j < SIZECLASS_FREE_LIST_SIZE; j++)
    {
        if (sizeClassFreeList[sizeclass].l[j].blockPtr != NULL && sizeClassFreeList[sizeclass].l[j].blockSize != 0)
            return FALSE;
    }
    return TRUE;
}

// Removes a memory block from the free-list, usually called by MALLOC during
// allocation of memory.

void removeBlockFromSizeClassFreeList(mdb ptr, int size)
{
    int i = 0;
    // finding the corresponding size-classes
    while (size > classSizeArray[i])
        i++;
    int j = 0;
    while(j<=sizeClassFreeList[i].rear && ptr != sizeClassFreeList[i].l[j].blockPtr)
    j++;
    if (j > sizeClassFreeList[i].rear)
    {
        perror("No block with the given pointer");
        return;
    }
    // swapping the memory blok pointer with the last element and then decreasing the rear position
    _sizeClass_free_list temp;
    temp = sizeClassFreeList[i].l[j];
    sizeClassFreeList[i].l[j] = sizeClassFreeList[i].l[sizeClassFreeList[i].rear];
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear] = temp;
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear].blockPtr = NULL;
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear].blockSize = 0;
    sizeClassFreeList[i].rear -= 1;
    return;
}
// adds memory block to the corresponding size-class freeList. called by FREe() function.
void addBlockToSizeClassFreeList(mdb ptr, int size, int offset)
{
    int i = 0;
    while (size > classSizeArray[i])
        i++;
    if (sizeClassFreeList[i].rear >= SIZECLASS_FREE_LIST_SIZE - 1)
        return;
    sizeClassFreeList[i].rear += 1;
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear].blockPtr = ptr;
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear].blockSize = size;
    sizeClassFreeList[i].l[sizeClassFreeList[i].rear].offset = offset;
    return;
}
// removes all the memory blocks from the list located at a particular page
// called by the FREE() function when the whole page is unused in order to return 
// it back to kernel
void removeAllFreeListBlocksFromOffset(int sizeclass, int offset)
{
    int i = 0;
    while (i <= sizeClassFreeList[sizeclass].l[i].offset == offset)
    {
        if (sizeClassFreeList[sizeclass].l[i].offset == offset)
        {
            _sizeClass_free_list temp;
            temp = sizeClassFreeList[sizeclass].l[i];
            sizeClassFreeList[sizeclass].l[i] = sizeClassFreeList[sizeclass].l[sizeClassFreeList[sizeclass].rear];
            sizeClassFreeList[sizeclass].l[sizeClassFreeList[sizeclass].rear] = temp;
            sizeClassFreeList[sizeclass].l[sizeClassFreeList[sizeclass].rear].blockPtr = NULL;
            sizeClassFreeList[sizeclass].l[sizeClassFreeList[sizeclass].rear].blockSize = 0;
            sizeClassFreeList[sizeclass].l[sizeClassFreeList[sizeclass].rear].offset = -1;
            sizeClassFreeList[sizeclass].rear -= 1;
        }
        i++;
    }
}

// returns memory block of the corresponding sizeclass to user called by 
// MALLOC() when freeList is not empty
mdb getFreeBlockFromFreeList(size_t bytes)
{
    int i = 0;
    while (i <= NUM_OF_CLASSES && bytes > classSizeArray[i])
        i++;
    mdb ptr;
    ptr = sizeClassFreeList[i].l[0].blockPtr;
    // removing it from the list as it will be used by the user
    removeBlockFromSizeClassFreeList(sizeClassFreeList[i].l[0].blockPtr, sizeClassFreeList[i].l[0].blockSize);
    return ptr;
}