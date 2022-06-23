#ifndef FREELIST_H
#define FREELIST_H

#define FREE_LIST_SIZE 100
#define GETLCHILD(i) (2 * i + 1)
#define GETRCHILD(i) (2 * i + 2)
#define GETPARENT(i) ((i - 1) / 2)

#include "largealloc.h"

typedef struct _free_list
{
    mdb blockPtr;
    int blockSize;
} _free_list;

typedef struct free_list
{
    _free_list list[FREE_LIST_SIZE];
    int rear;
    int size;
} free_list;
extern free_list freeList;

void initFreeList(free_list *);
void swapListElements(free_list *, int, int);
int addBlockToFreeList(free_list *, mdb);
void removeBlockFromFreeList(free_list *);
void heapifyFreeList();
int deleteBlockFromFreeList(free_list *, int, mdb);
int sortFreeList(free_list *);

#endif
