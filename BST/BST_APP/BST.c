#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BST.h"

// STACK

snode *top = NULL; 

bool isEmpty()
{
    return top ? false:true;
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
    snode *newNode=NULL;
    if (isFull())
        return;

    if(!(newNode = (snode *)malloc(sizeof(snode))))
	    return;

    newNode->record = record;
    newNode->next = top;
    top = newNode;
}

node *pop()
{
    node *record = NULL;
    snode *tmp = NULL;
    
    if (!isEmpty())
    {
	    tmp = top;
	    record = top->record;
	    top = top->next;
	    free(tmp);
    }

    return record;
}

void killStack()
{
    while (top)
        pop();

    return ;
}

// BST

int height(node *root)
{
    int x, y;
    if (!root)
        return 0;

    x = height(root->left);
    y = height(root->right);

    return x > y ? x + 1 : y + 1;
}

node *findMax(node *root) // inorder predecessor (max node in left)
{
    while (root && root->right)
        root = root->right;
    return root;
}

node *findMin(node *root) // inorder successor (min node in right)
{
    while (root && root->left)
        root = root->left;
    return root;
}

node *getNewNode(int key, char *name)
{
    node *newNode= NULL;
    
    if(!(newNode = (node *)malloc(sizeof(node))))
        return NULL;

    newNode->mis = key;
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;

    return newNode;
}

void initBST(bst *ptr)
{
    *ptr = NULL;
    return;
}

node *insertNode(bst *ptr, int key, char *name) // recursive
{
    static bool flag = false; // to check the first recursion
    node *p = *ptr;

    if (!p)
    {
        node *newNode = getNewNode(key, name);
        if (!flag) // empty tree
            *ptr = newNode;
        return newNode;
    }
    else
    {
        flag = true;
        if (p->mis < key)
            p->right = insertNode(&p->right, key, name);
        else if (p->mis > key)
            p->left = insertNode(&p->left, key, name);
        return p;
    }
}

node *removeNode(bst *ptr, int key) // recursive, will return root node when fully executed
{
    node *link = *ptr;
    if (!link) // empty tree or key not found
        return NULL;
    else if (link->mis < key)// search for node
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
            temp = findMin(link->right); // findMax(link->left);
            link->mis = temp->mis;
            link->right = removeNode(&(link->right), temp->mis);
        }
    }
    return link;
}

node *searchNode(bst t, int key) // recursive search
{
    if (!t) // empty tree or key not found
        return NULL;
    if (t->mis == key)
        return t;
    else if (t->mis < key)
        return searchNode(t->right, key);
    else
        return searchNode(t->left, key);
}

void postorder(bst p) // iterative postorder using stack
{
    // there is specific address mapping to negative as well as positive long int and {address <-----> long int}
    long int temp = 0;
    while (p || !isEmpty(top))
    {
        if (p)
        {
            push(p);
            p = p->left;
        }
        else
        {
            temp = (long int)pop(top);
            if (temp > 0) // address was pushed first time
            {
                push((node *)(-temp)); // make addresss negative as it is pushed second time
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
    killStack();
    return;
}

void displayLevel(bst root, int level)
{
    if (!root)
        return;

    if (level == 1)
        printf("%d : %s\n", root->mis, root->name);

    displayLevel(root->left, level - 1);
    displayLevel(root->right, level - 1);
}

void destroyTree(bst root) // destroying tree by postorder traversal
{
    if (!root)
        return;

    destroyTree(root->left);
    destroyTree(root->right);

    printf("%d : %s, deleting...\n",root->mis, root->name);
    free(root);
}
