// Main header file containing prototypes of functions
#ifndef BST_H
#define BST_H
typedef struct bst
{
	int *tree; // arr for storing tree
	int size;  // maximum capacity of arr tree
	// int length;//length of arr upto which tree is present, length -1 is the index of last element in tree
} bst;

void init_bst(bst *, int);
void insert_bst(bst *, int);
void recursive_traverse(bst, int);
int isComplete(bst);

#endif
