#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#endif
#include "defines.h"

int IsEmpty(struct StackNode *st)
{
    return st ? 0 : 1;
}
int IsFull()
{
    int r;
    struct StackNode *t;
    t = (struct StackNode *)malloc(sizeof(struct StackNode));
    r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
    free(t);
    return r;
}
void push(struct StackNode *st, node *x)
{
    if (IsFull())
    {
        // printf("Stack Overflow!");
        return;
    }
    struct StackNode *t;
    t = (struct StackNode *)malloc(sizeof(struct StackNode));
    t->x = x;
    t->next = st;
    top = t;
}
node *pop(struct StackNode *st)
{
    node *x = NULL;
    if (IsEmpty(st))
    {
        // printf("Stack Underflow!\n");
    }
    else
    {
        top = top->next;
        x = st->x;
    }
    return x;
}
void initBST(bst *t)
{
    *t = NULL;
    return;
}
void insertNode(bst *t, int x, char *n)
{
    node *nn = NULL;
    nn = (node *)malloc(sizeof(node));

    if (!nn)
    {
        free(nn);
        // printf("Overflow!\n");
        return;
    }

    nn->mis = x;
    nn->name = n;
    nn->left = nn->right = NULL;

    node *p, *q; // q is a trailing ptr of
    p = *t;
    q = NULL;

    if (!p) // if tree empty then make root point to nn
    {
        *t = nn;
        return;
    }

    while (p) // move p until it becomes null
    {
        if (p->mis == x)
        {
            printf("Duplicate Entry!\n");
            return;
        }

        q = p; // let q follow p
        if (p->mis < x)
            p = p->right;
        else
            p = p->left;
    }

    if (q->mis < x)
        q->right = nn;
    else
        q->left = nn;
    return;
}
int removeNode(bst *t, int key)
{
    return;
}
int search(bst t, int key)
{
    return;
}

void inorder(bst t)
{
    if (t)
    {
        inorder(t->left);
        printf("%d : %s\n", t->mis, t->name);
        inorder(t->right);
    }
}
void postOrder(bst t) // left right vlaue recursive
{

    // while(t || !IsEmpty(&top))
    // {
    //     if(t)
    //     {
    //         printf("%d : %s\n", t->mis,t->name);
    //         push(&top,t);
    //         t=t->left;
    //     }
    //     else
    //     {
    //         t=pop(&top);
    //         t=t->right;
    //     }
    // }
    return;
}
void displayLevel(bst t, int level)
{
    return;
}
void destroyTree(bst *t)
{
    return;
}