#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
typedef struct temp {
    int a,b,c,d;
}temp;

typedef struct largealloc {

    char arr[1024];
}largealloc;

int main() {

    
    largealloc *buffer;
    buffer = (largealloc*)MALLOC(sizeof(largealloc)*1024);

    int *arr;
    arr = (int *)MALLOC(sizeof(int)*5);
    for(int i = 0;i<5;i++) {
        arr[i] = i;
    }
    for(int j=0;j<5;j++) {
        printf("%d ",arr[j]);
    }
    printf("\n");
    arr = (int *)REALLOC(arr,sizeof(int)*10);
    for(int i =5;i<10;i++) {
        arr[i] = i;
    }

    for(int j=0;j<10;j++) {
        printf("%d ",arr[j]);
    }
    printf("\n");

    FREE(buffer);
    FREE(arr);
    

    return 0;
 }



