#ifndef SIZECLASS_FREELIST_H
#define SIZECLASS_FREELIST_H

#include "sizeclasses.h"

#define SIZECLASS_FREE_LIST_SIZE 100

typedef struct _sizeClass_free_list
{
    mdb blockPtr;
    int blockSize;
    int offset;
}_sizeClass_free_list;

typedef struct sizeClass_free_list
{
    _sizeClass_free_list l[SIZECLASS_FREE_LIST_SIZE];
    int rear;
}sizeClass_free_list;

extern sizeClass_free_list sizeClassFreeList[NUM_OF_CLASSES];

void initSizeClassFreeList();

mdb getFreeBlockFromFreeList(size_t);

void addBlockToSizeClassFreeList(mdb, int, int);

int isSizeClassFreeListEmpty(int);

void removeBlockFromSizeClassFreeList(mdb, int);

void removeAllFreeListBlocksFromOffset(int, int);

#endif
