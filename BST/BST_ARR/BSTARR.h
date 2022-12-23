#ifndef BST_H
#define BST_H

typedef struct bst
{
	int *tree;
	int size;
} bst;

void init_bst(bst *, int);
void insert_bst(bst *, int);
void recursive_traverse(bst, int);
bool is_complete(bst);

#endif
