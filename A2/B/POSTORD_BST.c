#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
} node;
typedef node *bst;

struct StackNode
{
    node *x;
    struct StackNode *next;
};
// stack functions

struct StackNode *top = NULL; // global ptr to a stack
node *StackTop(struct StackNode *st)
{
    if (st)
        return st->x;
    return NULL;
}
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
node *newNode(int x)
{
    node *nn = (node *)malloc(sizeof(node));
    if (!nn)
        return NULL;
    nn->data = x;
    nn->left = nn->right = NULL;
    return nn;
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
                printf("%d ", p->data);
                p = NULL;
            }
        }
    }
    KillStack(top);
    return;
}

void postorder2bst(int post[], int n, bst *root)
{
    node *t = NULL, *p = NULL;
    int i = n - 1;
    *root = newNode(post[i--]);
    p = *root;
    while (i >= 0)
    {
        if (post[i] > p->data)
        {
            t = newNode(post[i--]);
            p->right = t;
            push(top, p);
            p = t;
        }
        else // smaller should be within a range
        {
            if (post[i] < p->data && post[i] > (IsEmpty(top) ? INT_MIN : StackTop(top)->data))
            {
                t = newNode(post[i--]);
                p->left = t;
                p = t;
            }
            else
            {
                p = pop(top);
            }
        }
    }
    KillStack(top);
    return;
}
int main()
{
    bst t;
    int n;
    printf("Enter No. Elements in BST:");
    scanf(" %d", &n);
    int *post=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
        scanf(" %d", &post[i]);
    postorder2bst(post, n, &t);
    printf("\n");
    postorder(t);
    printf("\n");
    return 0;
}
