#include<stdio.h>
#include<stdlib.h>
#include "defines.h"
#include "BST.h"
int main()
{
    bst t;
    initBST(&t);
    insertNode(&t, 1, "A");
    insertNode(&t, 0, "B");
    insertNode(&t, 10, "C");
    insertNode(&t, 14, "D");
    insertNode(&t, 15, "E");
    insertNode(&t, 13, "F");
    insertNode(&t, 5, "G");
    insertNode(&t, 2, "H");
    insertNode(&t, 7, "I");
    insertNode(&t, 700, "J");
    printf("\n\n");
    inorder(t);
    printf("\n\n");
    return 0;
}
