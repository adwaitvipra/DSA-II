#ifndef STD_H
#define STD_H
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#endif
#include "BSTARR.h"

int main()
{
	bst x,y,z;
	init_bst(&x, 10);
	insert_bst(&x, 8);
	insert_bst(&x, 5);
	insert_bst(&x, 10);
	insert_bst(&x, 3);
	insert_bst(&x, 7);
	insert_bst(&x, 9);
	insert_bst(&x, 11);
	printf("Is BST Complete:\t%s\n",isComplete(x)?"True":"False");
	printf("Recursive Inorder Traverse:\t");
	recursive_traverse(x, 0);
	printf("\n");
	return 0;
}
