#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
} node;

typedef node *bst;

typedef struct snode 
{
    node *record;
    struct snode *next;
}snode;

// STACK

snode *top = NULL; // global ptr to a stack

node *stackTop()
{
	if(top)
		return top->record;
	return NULL;
}

bool isEmpty()
{
    return top ? false : true;
}

bool isFull()
{
    snode *tmpNode=NULL;

    if(!(tmpNode = (snode *)malloc(sizeof(snode))))
	    return true;

    free(tmpNode);
    return false;
}

void push(node *record)
{
	if(!isFull())
	{
		snode *newNode = NULL;
		if(!(newNode = (snode *)malloc(sizeof(snode))))
			;
		else
		{
			newNode->record = record;
			newNode->next = top;
			top = newNode;
		}
	}

	return ;
}

node *pop()
{
	snode *tmp = NULL;
	node *rec = NULL;

	if(!isEmpty())
	{
		tmp = top;
		rec = top->record;
		top = top->next;
		free(tmp);
	}

	return rec;

}

void killStack()
{
	while(top)
		pop();
	return ;
}

// BST functions

node *findMax(node *p) // inorder predecessor
{
    while (p && p->right)
        p = p->right;
    return p;
}

node *findMin(node *p) // inorder successor
{
    while (p && p->left)
        p = p->left;
    return p;
}

node *getNewNode(int val)
{
	node *newNode = NULL;

	if(!(newNode = (node *)malloc(sizeof(node))))
		;
	else
	{
		newNode->data = val;
		newNode->right = newNode->left = NULL;
	}

	return newNode;
}

void postorder(bst p) // iterative postorder using stack
{
    // there is specific address for negative as well as positive long int and I found that address <-----> long int
    long int temp = 0;
    while (p || !isEmpty())
    {
        if (p)
        {
            push(p);
            p = p->left;
        }
        else
        {
            temp = (long int)pop();
            if (temp > 0) // address was pushed first time
            {
                push((node *)(-temp)); // make addresss negative as it is pushed second time
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
    killStack();
    return;
}

void postorder2bst(int post[], int n, bst *root)
{
    node *t = NULL, *p = NULL;
    int i = n - 1;
    *root = getNewNode(post[i--]);
    p = *root;
    while (i >= 0)
    {
        if (post[i] > p->data)
        {
            t = getNewNode(post[i--]);
            p->right = t;
            push(p);
            p = t;
        }
        else // smaller should be within a range
        {
            if (post[i] < p->data && post[i] > (isEmpty() ? INT_MIN : stackTop()->data))
            {
                t = getNewNode(post[i--]);
                p->left = t;
                p = t;
            }
            else
            {
                p = pop();
            }
        }
    }
    killStack();
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
