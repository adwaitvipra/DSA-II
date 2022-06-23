#ifndef LARGE_ALLOC_H
#define LARGE_ALLOC_H

#include "memalloc.h"
#define MAX_SIZE_FOR_LARGE_ALLOC 100

typedef struct _large_alloc{
    mdb ptr;
    int offset;
    int remainingSize;
}large_alloc;

typedef struct _large_alloc_list
{
    large_alloc largeBlock[MAX_SIZE_FOR_LARGE_ALLOC];
    int count;
}large_alloc_list;

extern large_alloc_list largeAllocList;

int splitLargeBlock(mdb , size_t);

int mergeLargeBlock(mdb);
void *returnLargeBlock(size_t);

void LargeAllocInit();

int isLargeAllocPageEmpty(mdb);
void removeLargeAllocPage(mdb);

#endif