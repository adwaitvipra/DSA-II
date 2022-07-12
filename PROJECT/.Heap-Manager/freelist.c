#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <error.h>
#include "memalloc.h"
#include "freelist.h"

free_list freeList;
// initialize free list when called for first time
void initFreeList(free_list *l1)
{
    l1->size = FREE_LIST_SIZE;
    l1->rear = -1;
    for (int i = 0; i < FREE_LIST_SIZE; i++)
    {
        l1->list[i].blockPtr = NULL;
        l1->list[i].blockSize = 0;
    }
    return;
}
// swap two nodes of heap
void swapListElements(free_list *l1, int i, int j)
{
    _free_list temp;
    temp = l1->list[j];
    l1->list[j] = l1->list[i];
    l1->list[i] = temp;
    return;
}
// insert memory block to heap
int addBlockToFreeList(free_list *l1, mdb ptr)
{
    if (l1->rear == l1->size - 1)
        return INT_MIN;

    l1->rear++;
    l1->list[l1->rear].blockPtr = ptr;
    l1->list[l1->rear].blockSize = ptr->blockSize;

    int i = l1->rear;

    while (i > 0 && ptr->blockSize > l1->list[GETPARENT(i)].blockSize)
    {
        swapListElements(l1, i, GETPARENT(i));
        i = GETPARENT(i);
    }
    return 1;
}
// helper function to perform heapify operation on freelist heap
void heapifyFreeList()
{
    for (int i = 0; i < freeList.rear; i++)
    {
        if (freeList.list[i].blockSize > freeList.list[GETPARENT(i)].blockSize)
        {
            int j = i;
            while (freeList.list[j].blockSize > freeList.list[GETPARENT(j)].blockSize)
            {
                swapListElements(&freeList, j, GETPARENT(j));
                j = GETPARENT(j);
            }
        }
    }
}
// removes first element of the freelist heap
void removeBlockFromFreeList(free_list *l1)
{
    if (l1->rear == -1)
        return;

    _free_list x = l1->list[0];
    l1->list[0] = l1->list[l1->rear];
    l1->list[l1->rear] = x;
    l1->rear--;
    int i = 0;
    int max = 0;
    while (i < l1->rear) // heapify top-down
    {
        int left = GETLCHILD(i);
        int right = GETLCHILD(i);
        if (left > l1->rear)
            return;
        if (right > l1->rear)
        {
            if (l1->list[i].blockSize < l1->list[left].blockSize)
                swapListElements(l1, i, left);
            return;
        }
        if (l1->list[left].blockSize > l1->list[right].blockSize)
            max = left;
        else
            max = right;
        swapListElements(l1, i, max);
        i = max;
    }
    return;
}
// removes any element from freelist, called by MALLOC() while
// allocating memory from freelist
int deleteBlockFromFreeList(free_list *l1, int size, mdb m1)
{
    if (!l1 || !l1->list)
        return INT_MIN;

    int i = 0;
    while (i < FREE_LIST_SIZE && l1->list[i].blockSize != size && l1->list[i].blockPtr != m1)
        i++;
    if (i >= FREE_LIST_SIZE)
        return INT_MIN;

    l1->list[i] = l1->list[l1->rear];
    l1->list[l1->rear].blockPtr = NULL;
    l1->list[l1->rear].blockSize = 0;
    l1->rear--;
    heapifyFreeList();
    return 1;
}
// sorts the freelist
int sortFreeList(free_list *l1)
{
    heapifyFreeList();
    for (int i = l1->rear; i > 0; i++)
    {
        swapListElements(l1, 0, i);
        int j = 0, index;
        do
        {
            index = GETLCHILD(j);
            if (l1->list[index].blockSize < l1->list[GETLCHILD(j)].blockSize && index < (i - 1))
                i++;
            if (l1->list[j].blockSize < l1->list[index].blockSize && index < i)
                swapListElements(l1, j, index);
            j = index;
        } while (index < i);
    }
    return 1;
}