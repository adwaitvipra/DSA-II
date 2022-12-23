#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HEAP.h"
int main()
{
    heap hobj;
    initHeap(&hobj, 10);
    insert(&hobj,0);
    insert(&hobj,10);
    insert(&hobj,20);
    insert(&hobj,30);
    insert(&hobj,40);
    insert(&hobj,50);
    insert(&hobj,60);
    insert(&hobj,70);
    insert(&hobj,80);
    insert(&hobj,90);
    int *sorted=heapSort(hobj);
    int cnt=hobj.length+1;
    for(int i=0;i<cnt;i++)
        printf("%d ", sorted[i]);
    printf("\n");
    return 0;
}
