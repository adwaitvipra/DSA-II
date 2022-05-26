#include<stdio.h>
#include "EXPTREE.h"
int main()
{
	EXP tree;
	initTree(&tree);
	printf("Traversing Given Expression Tree:");
	Traverse(tree);
	printf("\n");
	printf("Answer = %f",Compute(tree));
	printf("\n");
	return 0;
}
