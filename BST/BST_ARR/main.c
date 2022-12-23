#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include "BSTARR.h"

int main()
{
	bst x;
	init_bst(&x, 10);
	insert_bst(&x, 8);
	insert_bst(&x, 5);
	insert_bst(&x, 10);
	insert_bst(&x, 3);
	insert_bst(&x, 7);
	insert_bst(&x, 9);
	insert_bst(&x, 11);
	printf("Is BST Complete:\t%s\n",is_complete(x)?"True":"False");
	printf("Recursive Inorder Traverse:\t");
	recursive_traverse(x, 0);
	printf("\n");
	return 0;
}
