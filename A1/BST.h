#include "BST.c"
//This file contains all the function prototypes
void initBST(bst*);
void insertNode(bst*, int, char* );
int removeNode(bst *, int);
int search(bst,int);
void postOrder(bst);
void displayLevel(bst ,int);
void destroyTree(bst *);