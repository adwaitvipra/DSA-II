#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"
// stack functions
struct StackNode *top = NULL; // global ptr to a stack
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
        return x;
    }
    else
    {
        top = top->next;
        x = st->x;
    }
    return x;
}
void KillStack(struct StackNode *st)
{
    if (!st)
        return;
    while (st)
    {
        pop(st);
    }
}
// BST functions
int Height(node *p)
{
    int x, y;
    if (!p)
        return 0;
    x = Height(p->left);
    y = Height(p->right);
    return x > y ? x + 1 : y + 1;
}
node *FindMax(node *p) // inorder predecessor
{
    while (p && p->right)
        p = p->right;
    return p;
}
node *FindMin(node *p) // inorder successor
{
    while (p && p->left)
        p = p->left;
    return p;
}
node *newNode(int x, char *n)
{
    node *nn = (node *)malloc(sizeof(node));
    if (!nn)
        return NULL;
    nn->mis = x;
    for (int i = 0; i < strlen(n); i++)
        nn->name[i] = n[i];
    nn->left = nn->right = NULL;
    return nn;
}
void initBST(bst *t)
{
    *t = NULL;
    return;
}
node *insertNode(bst *t, int x, char *n) // recursive
{

    node *p = *t;
    static node *q = NULL;
    if (!p)
    {
        node *nn = newNode(x, n);
        if (!q) // empty tree
            *t = nn;
        else
            return nn;
    }
    else
    {
        q = p;
        if (p->mis < x)
            p->right = insertNode(&p->right, x, n);
        else if (p->mis > x)
            p->left = insertNode(&p->left, x, n);
        return p;
    }
}
node *removeNode(bst *t, int key) // recursive, will return root node when fully executed
{
    node *link = *t;
    if (!link) // empty tree or key not found
        return NULL;
    // search for node
    else if (link->mis < key)
        link->right = removeNode(&(link->right), key);
    else if (link->mis > key)
        link->left = removeNode(&(link->left), key);
    else // node found
    {
        // case 1:No child
        if (!link->right && !link->left)
        {
            free(link);
            link = NULL; // set dangling ptr link to null
        }
        // case 2:One child
        else if (!link->right)
        {
            node *temp = NULL;
            temp = link;
            link = link->left; // move link to left
            free(temp);
            temp = NULL;
        }
        else if (!link->left)
        {
            node *temp = NULL;
            temp = link;
            link = link->right; // move link to right
            free(temp);
            temp = NULL;
        }
        // case 3: Two childs
        else
        {
            node *temp = NULL;
            // inorder predecessor or inorder successor
            temp = FindMin(link->right); // FindMax(link->left);
            link->mis = temp->mis;
            link->right = removeNode(&(link->right), temp->mis);
        }
    }
    return link;
}
node *search(bst t, int key) // recursive search
{
    if (!t) // empty tree or key not found
        return NULL;
    if (t->mis == key)
        return t;
    else if (t->mis < key)
        return search(t->right, key);
    else
        return search(t->left, key);
}
void postorder(bst p) // iterative postorder using stack
{
    // there is specific address for negative as well as positive long int and I found that address <-----> long int
    long int temp = 0;
    while (p || !IsEmpty(top))
    {
        if (p)
        {
            push(top, p);
            p = p->left;
        }
        else
        {
            temp = (long int)pop(top);
            if (temp > 0) // address was pushed first time
            {
                push(top, (node *)(-temp)); // make addresss negative as it is pushed second time
                p = ((node *)(temp))->right;
            }
            else // address is negative so make the p point on positive value of address by negating negative temp
            {
                p = (node *)(-temp);
                printf("%d : %s\n", p->mis, p->name);
                p = NULL;
            }
        }
    }
    KillStack(top);
    return;
}
void displayLevel(bst t, int level)
{
    if (!t)
        return;
    if (level == 1)
    {
        printf("%d : %s\n", t->mis, t->name);
    }
    displayLevel(t->left, level - 1);
    displayLevel(t->right, level - 1);
}
void destroyTree(bst *t) // destroying tree by postorder traversal
{
    node *p = *t;
    if (!p)
        return;
    destroyTree(&(p->left));
    destroyTree(&(p->right));
    printf("%d : %s, deleting...\n", p->mis, p->name);
    free(p);
}