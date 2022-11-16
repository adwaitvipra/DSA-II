#ifndef HEAP_H
#define HEAP_H
typedef struct
{
    int *H;
    int size;
    int length;
} heap;

int isFull(heap*);
int isEmpty(heap*);
void initHeap(heap *, int);
void insert(heap *,int);
int returnMax(heap *);
void heapify(heap *,int);
void adjust(heap *);
int *heapSort(heap);
#endif