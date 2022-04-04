#include<stdio.h>
#include<stdlib.h>

typedef struct Node //creating node
{
    int mis;
    char name[10];
    struct Node *left, *right;
} node;

typedef node *bst; //typecasting a ptr to node as bst

void intiBST(bst *t)
{
    *t = NULL;
    return;
}
void insertNode(bst *t, int x)
{

}
int removeNode(bst *t, int key)
{

}
int search(bst t, int key)
{

}
void postOrder(bst t)
{

}
void displayLevel(bst t, int level)
{

}
void destroyTree(bst *t)
{

}