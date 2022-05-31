#include <stdio.h>
#include <stdlib.h>
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
int isFull(heap *h)
{
    if (h->length == h->size - 1)
        return 1;
    return 0;
}
int isEmpty(heap *h)
{
    if (h->length == -1)
        return 1;
    return 0;
}
void initHeap(heap *h, int s)
{
    h->H = (int *)malloc(sizeof(int) * s);
    h->size = s;
    h->length = -1;
    return;
}

void insert(heap *h, int x)
{
    // 1. Check if given heap is full.
    // 2. If not full then increment length and insert new value at lenght th index in heap.
    // 3. Now heapify until child is in rule (min/max) and parent is greater than root (0)

    if (isFull(h))
        return;
    int child = ++h->length;
    h->H[child] = x;
    heapify(h, child);
    return;
}
int returnMax(heap *h)
{
    // 1. check if given heap is empty.
    // 2. if not empty then return the rule ele (min/max), swap 0th ele with h.length th ele and decrement length
    // 3. adjust the heap i.e. heapify from top to down
    if (isEmpty(h))
        return INT_MIN;
    int x = h->H[0];
    swap(&h->H[0], &h->H[h->length--]);
    adjust(h);
    return x;
}

void heapify(heap *h, int child)
{
    int parent = (child - 1) / 2;
    int n = h->H[child];
    int pn = h->H[parent];

    if (n > pn && (parent >= 0 && child <= h->length))
    {
        swap(&h->H[child], &h->H[parent]);
        heapify(h, parent);
    }
    return;
}
void adjust(heap *h)
{
    int parent = 0;
    int max = INT_MIN;

    while (parent <= h->length)
    {
        int lc = parent * 2 + 1;
        int rc = parent * 2 + 2;
        int ln = h->H[lc];
        int rn = h->H[rc];

        if (lc <= h->length)
        {
            if (rc <= h->length) // right child exists
            {
                if (ln >= rn) // left node is greater than or equal to right node
                    max = lc;
                else // right node is greater than left node
                    max = rc;
            }
            else // only left child exists
                max = lc;

            if (h->H[parent] < h->H[max])
            {
                swap(&h->H[parent], &h->H[max]);
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

int* heapSort(heap h)
{
    int *sorted=(int *)malloc(sizeof(int)*(h.length+1));
    int cnt=h.length+1;
    for(int i=0;i<cnt;i++)
    {
        sorted[i]=returnMax(&h);
    }
    return sorted;
}

