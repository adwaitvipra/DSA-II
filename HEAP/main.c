#include <stdio.h>
#include <stdlib.h>
#include "HEAP.h"
int main()
{
    heap h;
    initHeap(&h, 10);
    insert(&h,0);
    insert(&h,10);
    insert(&h,20);
    insert(&h,30);
    insert(&h,40);
    insert(&h,50);
    insert(&h,60);
    insert(&h,70);
    insert(&h,80);
    insert(&h,90);
    int *sorted=heapSort(h);
    int cnt=h.length+1;
    for(int i=0;i<cnt;i++)
        printf("%d ", sorted[i]);
    printf("\n");
    return 0;
}