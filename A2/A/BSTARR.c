#ifndef STD_H
#define STD_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#endif
#include "BSTARR.h"

void init_bst(bst *t, int n) // mallocs, sets all the elements with min int
{
	int i;
	t->tree = (int *)malloc(sizeof(int) * n);
	t->size = n;
	for (i = 0; i < n; i++) // init arr with min int value
		t->tree[i] = INT_MIN;
	return;
}
void insert_bst(bst *t, int x) // non-recursive function
{
	int i = 0;
	if (t->tree[0] == INT_MIN)
	{
		t->tree[0] = x;
		return;
	}
	while (i < t->size && t->tree[i] != INT_MIN)
	{
		if (t->tree[i] == x) // duplicate
			return;
		if (t->tree[i] < x) // right child
			i = 2 * i + 2;
		else // left child
			i = 2 * i + 1;
	}
	if (i < t->size)
		t->tree[i] = x;
	return;
}
void recursive_traverse(bst t, int p)
{
	if (p< t.size && t.tree[p] != INT_MIN)
	{
		recursive_traverse(t, 2 * p + 1); // traverse left subtree
		printf("%d ", t.tree[p]);		  // print the value
		recursive_traverse(t, 2 * p + 2); // traverse right subtree
	}
	return;
}
int isComplete(bst t)
{
	int i;
	int flag = 1;
	for (i = 0; i < t.size - 1; i++)
	{
		if (t.tree[i] == INT_MIN && t.tree[i + 1] != INT_MIN)
		{
			flag = 0;
			break;
		}
	}
	return flag ? 1 : 0;
}
