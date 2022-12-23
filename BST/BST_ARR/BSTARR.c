#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "BSTARR.h"

void init_bst(bst *tptr, int size) // mallocs, sets all the elements with min int
{
	tptr->tree = (int *)malloc(sizeof(int) * size);
	tptr->size = size;
	for (int i = 0; i < size; i++) // init arr with min int value
		tptr->tree[i] = INT_MIN;
	return;
}

void insert_bst(bst *tptr, int val) // non-recursive function
{
	int i = 0;
	if (tptr->tree[0] == INT_MIN) // empty tree
	{
		tptr->tree[0] = val;
		return;
	}

	while (i < tptr->size && tptr->tree[i] != INT_MIN)
	{
		if (tptr->tree[i] == val) // duplicate
			return;
		if (tptr->tree[i] < val) // right child
			i = 2 * i + 2;
		else // left child
			i = 2 * i + 1;
	}
	if (i < tptr->size)
		tptr->tree[i] = val;
	return;
}

void recursive_traverse(bst tree, int pidx)
{
	if (pidx < tree.size && tree.tree[pidx] != INT_MIN)
	{
		recursive_traverse(tree, 2 * pidx + 1); // traverse left subtree
		printf("%d ", tree.tree[pidx]);		  // print the value
		recursive_traverse(tree, 2 * pidx + 2); // traverse right subtree
	}
	return;
}

bool is_complete(bst tree)
{
	bool flag = true;
	for (int i = 0; i < tree.size - 1; i++)
	{
		if (tree.tree[i] == INT_MIN && tree.tree[i + 1] != INT_MIN)
		{
			flag = false;
			break;
		}
	}
	return flag ? true : false;
}
