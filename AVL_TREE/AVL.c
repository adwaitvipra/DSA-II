#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "AVL.h"

int balanceFactor(AVL currNode)
{
    int x;
    if (!currNode)
        return 0;
    x = currNode->bf > '0' ? currNode->bf - '0' : '0' - currNode->bf;
    return x;
}

int height(AVL currNode)
{
    int hl, hr;
    if (!currNode)
        return 0;
    hl = height(currNode->leftChild);  // height of left subtree
    hr = height(currNode->rightChild); // height of right subtree
    // height of currNode will be whichever is greater of hl and hr plus one
    return hl > hr ? hl + 1 : hr + 1;
}

void initAVL(AVL *tree)
{
    *tree = NULL;
    return;
}

void adjust(AVL *parentNode) // updates the bf for the ancestors of a node
{
    int diff;
    node *currNode = *parentNode;

    if (!currNode)
        return;

    diff = height(currNode->leftChild) - height(currNode->rightChild);
    currNode->bf = diff >= 0 ? '0' + diff : '0' - diff;

    adjust(&(currNode->parent)); // call again to update the parents bf
}

node *imbalance(AVL parentNode)
{
    node *currNode = parentNode;
    if (!currNode)
        return NULL;

    // if (currNode->bf < ('0' - 1) || currNode->bf > ('0' + 1)) 
    // check for imbalance
    if (balanceFactor(currNode) < -1 || balanceFactor(currNode) > 1)
        return currNode;
    return imbalance(currNode->parent);
}

node *FindMax(node *p) // inorder predecessor
{
    while (p && p->rightChild)
        p = p->rightChild;
    return p;
}

node *FindMin(node *p) // inorder successor
{
    while (p && p->leftChild)
        p = p->leftChild;
    return p;
}

// rotations

void LL_Rotate(node *imbNode)
{
    node *x = imbNode;
    node *y = imbNode->leftChild;
    node *beta = y->rightChild;
    // make y's parent as x's parent
    y->parent = x->parent;
    // make x's parent y
    x->parent = y;
    // make y's right child, left child of x (if exists)
    if (beta)
    {
        beta->parent = x;
        x->leftChild = beta;
    }
    else
        x->leftChild = NULL;
    // make y's right child x
    y->rightChild = x;
    // adjust the x
    adjust(&imbNode);
    return;
}

void RR_Rotate(node *imbNode)
{
    node *x = imbNode;
    node *y = imbNode->rightChild;
    node *beta = y->leftChild;
    // make y's parent as x's parent
    y->parent = x->parent;
    // make x's parent y
    x->parent = y;
    // make y's left child, right child of x (if exists)
    if (beta)
    {
        beta->parent = x;
        x->rightChild = beta;
    }
    else
        x->rightChild = NULL;
    // make y's left child x
    y->leftChild = x;
    // adjust the x
    adjust(&imbNode);
    return;
}

void LR_Rotate(node *imbNode)
{
    RR_Rotate(imbNode->leftChild);
    LL_Rotate(imbNode);
    return;
}

void RL_Rotate(node *imbNode)
{
    LL_Rotate(imbNode->rightChild);
    RR_Rotate(imbNode);
    return;
}

void rotation(node *imbNode, node *childNode)
{
    int bfimb = balanceFactor(imbNode);                                 //
    int dir = ((strcmp(imbNode->month, childNode->month)) < 0) ? 0 : 1; // 0 for left, 1 for right
    int bfchild = dir != 0 ? balanceFactor(imbNode->rightChild) : balanceFactor(imbNode->leftChild);
    // 2, 1 LL
    if (bfimb == 2 && bfchild == 1)
        LL_Rotate(imbNode);
    //-2, -1 RR
    else if (bfimb == -2 && bfchild == -1)
        RR_Rotate(imbNode);
    // 2, -1 LR
    else if (bfimb == 2 && bfchild == -1)
        LR_Rotate(imbNode);
    //-2, 1 RL
    else if (bfimb == -2 && bfchild == 1)
        RL_Rotate(imbNode);
    return;
}

static node *nnins = NULL;

node *auxInsert(node *t, node *pt, const char *x) // root must be passed and root should take return value
{                                                 // multiple links are modified in this function, returning ptr to a struct Node
    if (!t)
    {
        node *nn = (node *)malloc(sizeof(node));
        strcpy(nn->month, x);
        nn->bf = '0';
        nn->leftChild = nn->rightChild = NULL;
        nn->parent = pt;
        nnins = nn;
        return nn;
    }

    if (strcmp(t->month, x) < 0)
    {
        t->rightChild = auxInsert(t->rightChild, t, x);
    }
    else if (strcmp(t->month, x) > 0)
    {
        t->leftChild = auxInsert(t->leftChild, t, x);
    }
    return t;
}

int insertNode(AVL *currNode, const char *x)
{
    node *temp = *currNode;
    node *imbNode = NULL;
    *currNode = auxInsert(temp, NULL, x); // insert same as BST
    adjust(&nnins->parent);               // adjust balance factors of ancestors
    imbNode = imbalance(nnins->parent);   // check if there is imbalanced node
    if (imbNode)                          // if imbalance exists then do suitable rotations
    {
        rotation(imbNode, nnins);
        return 1;
    }
    return 0;
}

// Remove Node
node *removeNode(AVL *currNode, const char *key) // recursive, will return root node when fully executed
{
    node *link = *currNode;
    if (!link) // empty tree or key not found
        return NULL;
    else if (strcmp(link->month, key) < 0)
        link->rightChild = removeNode(&(link->rightChild), key);
    else if (strcmp(link->month, key) > 0)
        link->leftChild = removeNode(&(link->leftChild), key);
    else // node found
    {
        node *dad = link->parent;
        node *imbNode = NULL;
        // case 1:No child
        if (!link->rightChild && !link->leftChild)
        {
            free(link);
            link = NULL; // set dangling ptr link to null
        }
        // case 2:One child
        else if (!link->rightChild)
        {
            node *temp = NULL;
            temp = link;
            link = link->leftChild; // move link to left
            free(temp);
            temp = NULL;
        }
        else if (!link->leftChild)
        {
            node *temp = NULL;
            temp = link;
            link = link->rightChild; // move link to right
            free(temp);
            temp = NULL;
        }
        // case 3: Two childs
        else
        {
            node *temp = NULL;
            // inorder predecessor or inorder successor
            temp = FindMin(link->rightChild); // FindMax(link->left);
            dad = temp->parent;               // make dad to point on parent of in order successor
            strcpy(link->month, temp->month);
            link->rightChild = removeNode(&(link->rightChild), temp->month);
        }
        // update the bf of ancestors
        adjust(&dad);
        // find imbalanced node
        imbNode = imbalance(dad);
        if (imbNode) // rotations if imbalanced node exists
            rotation(imbNode, dad);
    }
    return link;
}

void traverse(AVL currNode) // inorder traversal
{
    if (!currNode) // root is not null
        return;
    traverse(currNode->leftChild); // traverse left subtree
    printf("%s\n", currNode->month);
    traverse(currNode->rightChild); // traverse right subtree
}

void destroyTree(AVL *root)
{
    node *currentNode = *root;
    if (!currentNode)
        return;
    destroyTree(&(currentNode->leftChild));
    destroyTree(&(currentNode->rightChild));
    free(currentNode);
}
