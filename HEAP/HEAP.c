#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "HEAP.h"

// Max Heap
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

bool isFull(heap *hptr)
{
    if (hptr->length == hptr->size - 1)
        return true;
    return false;
}

bool isEmpty(heap *hptr)
{
    if (hptr->length == -1)
        return true;
    return false;
}

void initHeap(heap *hptr, int size)
{
    hptr->H = (int *)malloc(sizeof(int) * size);
    hptr->size = size;
    hptr->length = -1;
    return;
}

void insert(heap *hptr, int val)
{
    // 1. Check if given heap is full.
    // 2. If not full then increment length and insert new value at (length)th index in heap.
    // 3. Now heapify until child is in rule (min/max) and parent is greater than root (0)

	int child;
    if (isFull(hptr))
    	;
    else
    {
    	child = ++(hptr->length);
    	hptr->H[child] = val;
    	heapify(hptr, child);
    }
    return;
}

int returnMax(heap *hptr)
{
    // 1. check if given heap is empty.
    // 2. if not empty then return the rule ele (min/max), swap 0th ele with (h.length)th ele and decrement length
    // 3. adjust the heap i.e. heapify from top to down'

	int max = INT_MIN;
    if (!isEmpty(hptr))
    {
	    max = hptr->H[0];
	    swap(&(hptr->H[0]), &(hptr->H[hptr->length--]));
	    adjust(hptr);
    }

    return max;
}

void heapify(heap *hptr, int child)
{
    int parent = (child - 1) / 2;
    int *childNode = &(hptr->H[child]);
    int *parentNode = &(hptr->H[parent]);

    if (*childNode > *parentNode && (parent >= 0 && child <= hptr->length))
    {
        swap(childNode, parentNode);
        heapify(hptr, parent);
    }

    return;
}

void adjust(heap *hptr)
{
    int parent = 0;
    int max = INT_MIN;
    int leftChild, rightChild, leftNode, rightNode;

    while (parent <= hptr->length)
    {
        leftChild = parent * 2 + 1;
        rightChild = parent * 2 + 2;
        leftNode = hptr->H[leftChild];
        rightNode = hptr->H[rightChild];

        if (leftChild <= hptr->length)
        {
            if (rightChild <= hptr->length) // right child exists
            {
                if (leftNode >= rightNode) // left node is greater than or equal to right node
                    max = leftChild;
                else // right node is greater than left node
                    max = rightChild;
            }
            else // only left child exists
                max = leftChild;

            if (hptr->H[parent] < hptr->H[max])
            {
                swap(&(hptr->H[parent]), &(hptr->H[max]));
                parent = max;
            }
            else
                return;
        }
        else // neither left nor right child exists
            return;
    }
    return;
}

int* heapSort(heap hobj)
{
    int *sorted=NULL;
    int cnt=hobj.length+1;

    if(!(sorted = (int *)malloc(sizeof(int)*(hobj.length+1))))
	    return NULL;

    for(int i=0;i<cnt;i++)
        sorted[i]=returnMax(&hobj);

    return sorted;
}

