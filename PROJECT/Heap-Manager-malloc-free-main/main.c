#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

typedef struct largealloc
{

    char arr[1024];
} largealloc;

int main()
{

    // allocation from large alloc
    largealloc *buf;
    buf = (largealloc *)myMalloc(sizeof(largealloc) * 1024);

    for(int i=0;i<1024;i++)
    printf("%d ", buf->arr[i]);
    printf("\n\n");
    int *arr;
    arr = (int *)myMalloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    for (int j = 0; j < 5; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");
    arr = (int *)myRealloc(arr, sizeof(int) * 10);
    for (int i = 5; i < 10; i++)
    {
        arr[i] = i;
    }

    for (int j = 0; j < 10; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");

    int *callarr = (int *)myCalloc(10, sizeof(int));
    for (int j = 0; j < 10; j++)
    {
        printf("%d ", callarr[j]);
    }
    printf("\n");

    myFree(buf);
    myFree(arr);
    myFree(callarr);
    return 0;
}
