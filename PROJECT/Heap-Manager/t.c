#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *t;
    for(int i=0;i<10;i++)
    {
        t=(int*)malloc(sizeof(int));
        printf("%p\n", t);
    }
    return 0;
}
