// This file contains all the function prototypes and struct defination
#ifndef BST_H
#define BST_H

typedef struct Node // creating a struct for node
{
    int mis;
    char name[128];
    struct Node *left, *right;
} node;
typedef node *bst; // typecasting a ptr to node as bst

typedef struct stackNode
{
    node *record;
    struct stackNode *next;
} snode;

void initBST(bst *);
node *insertNode(bst *, int, char *);
node *removeNode(bst *, int);
node *searchNode(bst, int);
void postorder(bst);
void displayLevel(bst, int);
void destroyTree(bst );

#endif //BST_H
