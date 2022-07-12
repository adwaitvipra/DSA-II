#include <stdio.h>
#include <stdlib.h>
#include "sizeclasses.h"

pageList sizeClassList[NUM_OF_CLASSES][MAX_PAGES];

int classSizeArray[NUM_OF_CLASSES] = {
    4, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 160, 176, 184, 192, 208, 224, 240, 256, 272, 288, 312, 336, 368, 408, 448, 480, 512, 576, 640, 704, 768, 896, 1024

};

// initializes the sizeClassList when called by MALLOC for the first time
void initSizeClassList()
{
    for (int i = 0; i < NUM_OF_CLASSES; i++)
    {
        for (int j = 0; j < MAX_PAGES; j++)
        {
            sizeClassList[i][j].head = NULL;
            sizeClassList[i][j].availableBins = -1;
        }
    }
    return;
}

// allocates memory page from the kernel, divides it into corresponding size-class
void createSizeClassPage(int sizeclass, int offset)
{
    if (!sizeClassList[sizeclass][offset].head && sizeClassList[sizeclass][offset].availableBins == -1)
    {
        // allocating 1 page for all sizeclasses except for last class of 1024 bytes.
        if (sizeclass != 41)
        {
            sizeClassList[sizeclass][offset].head = (mdb)getPages(1);
            sizeClassList[sizeclass][offset].availableBins = TOTAL_BINS_IN_CLASS(1, classSizeArray[sizeclass]);
            // dividing it into corresponding size-class
            createSizeClassBinsList(&(sizeClassList[sizeclass][offset].head), classSizeArray[sizeclass], 1);
        }
        else if (sizeclass == 41)
        {
            sizeClassList[sizeclass][offset].head = (mdb)getPages(2);
            sizeClassList[sizeclass][offset].availableBins = TOTAL_BINS_IN_CLASS(2, classSizeArray[sizeclass]);
            // dividing it into corresponding size-class
            createSizeClassBinsList(&(sizeClassList[sizeclass][offset].head), classSizeArray[sizeclass], 2);
        }
    }
    return;
}

// returns the page containing atleast one free block from the corresponding size-class
mdb getPageForAllocation(int sizeclass)
{
    // if the size-class is in initialized state(No memory allocation is done no that size-class)
    int i = 0;
    if (!sizeClassList[sizeclass][0].head && sizeClassList[sizeclass][0].availableBins == -1)
    {
        createSizeClassPage(sizeclass, 0);
        sizeClassList[sizeclass][0].availableBins -= 1;
        return sizeClassList[sizeclass][0].head;
    }
    while (i < MAX_PAGES && sizeClassList[sizeclass][i].availableBins < 1 && sizeClassList[sizeclass][i].availableBins != -1)
        i++;
    // memory full
    if (i >= MAX_PAGES)
        return NULL;
    else if (sizeClassList[sizeclass][i].availableBins == -1)
    {
        sizeClassList[sizeclass][i].availableBins == -1;
        return sizeClassList[sizeclass][i].head;
    }
    // if no free block is available, allocate a new page for the size-class
    else if (sizeClassList[sizeclass][i].availableBins == -1)
    {
        createSizeClassPage(sizeclass, i);
        sizeClassList[sizeclass][i].availableBins == -1;
        return sizeClassList[sizeclass][i].head;
    }
    return NULL;
}

// divides the memory pages into doubly linked list of size-classes of the corresponding size.
void createSizeClassBinsList(mdb *head, int binSize, int noOfPages)
{
    if (!head)
        return;

    int binNum;
    binNum = noOfPages * SYS_PG_SZ / (binSize + METABLOCK_SIZE);

    mdb a, prev = NULL;
    a = *head;
    for (int i = 0; i < binNum; i++)
    {
        a->prevBlock = prev;
        a->blockSize = binSize;
        a->isFree = TRUE;
        a->headPtr = *head;
        // next location of the meta data block after the data block
        a->nextBlock = (mdb)(((char *)a) + METABLOCK_SIZE + binSize);
        prev = a;
        a = a->nextBlock;
    }
    // for the last node of the linked list
    a->prevBlock = prev;
    a->blockSize = binSize;
    a->isFree = TRUE;
    a->nextBlock = NULL;
    return;
}

// checks if the memory page is empty, returns true if true and vice-versa.
int isSizeClassPageEmpty(int sizeclass, int offset)
{
    mdb mptr;
    mptr = sizeClassList[sizeclass][offset].head;
    while (mptr)
    {
        if (mptr->isFree == FALSE)
            return FALSE;
        mptr = mptr->nextBlock;
    }
    return TRUE;
}
// wrapper function to freePage() used to free page from sizeClassList
void removeEmptySizeClassPage(int sizeclass, int offset)
{
    if (isSizeClassPageEmpty(sizeclass, offset) == TRUE)
    {
        int j = MAX_PAGES - 1;
        while (j >= 0 && sizeClassList[sizeclass][j].availableBins == -1 && !sizeClassList[sizeclass][j].head)
            j--;
        if (!j)
        {
            if (classSizeArray[sizeclass] == 1024)
                freePages(sizeClassList[sizeclass][j].head, 2);
            else
                freePages(sizeClassList[sizeclass][j].head, 1);

            sizeClassList[sizeclass][j].head == NULL;
            sizeClassList[sizeclass][j].availableBins == -1;
            return;
        }
        pageList temp;
        temp = sizeClassList[sizeclass][offset];
        sizeClassList[sizeclass][offset] = sizeClassList[sizeclass][j];
        sizeClassList[sizeclass][j]=temp;
        if (classSizeArray[sizeclass] == 1024)
            freePages(sizeClassList[sizeclass][j].head, 2);
        else
            freePages(sizeClassList[sizeclass][j].head, 1);
        sizeClassList[sizeclass][j].head = NULL;
        sizeClassList[sizeclass][j].availableBins = -1;
    }
    return;
}