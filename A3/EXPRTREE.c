#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE 100
int isValid(const char*);
void infix2postfix(const char *);
//#####################################################################################################################################################
//
//#####################################################################################################################################################
char *infix = NULL, *postfix = NULL; // global char ptrs
// Expression Tree Node Struct
typedef struct treeNode
{
	char character;
	struct treeNode *left, *right;
} node;
typedef node *EXP;

//#####################################################################################################################################################
//
//#####################################################################################################################################################

// postfix to expression tree stack node struct
typedef struct PfEtStack
{
	node *x;
	struct PfEtStack *next;
} petsnode;
// stack functions

petsnode *top = NULL; // global ptr to a stack
node *StackTopPet(petsnode *st)
{
	if (st)
		return st->x;
	return NULL;
}
int IsEmptypets(petsnode *st)
{
	return !st ? 1 : 0;
}
int IsFullpets()
{
	int r;
	petsnode *t;
	t = (petsnode *)malloc(sizeof(petsnode));
	r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
	free(t);
	return r;
}
void petspush(petsnode *st, node *x)
{
	if (IsFullpets())
	{
		return;
	}
	petsnode *t;
	t = (petsnode *)malloc(sizeof(petsnode));
	t->x = x;
	t->next = st;
	top = t;
}
node *petspop(petsnode *st)
{
	node *x = NULL;
	if (IsEmptypets(st))
	{
		return x;
	}
	else
	{
		top = top->next;
		x = st->x;
	}
	return x;
}
void killpets(petsnode *st)
{
	if (!st)
		return;
	while (st)
	{
		petspop(st);
	}
}

//#####################################################################################################################################################
//
//#####################################################################################################################################################

// Infix to Postfix Stack
// array representation of stack for infix to postfix
typedef struct PfStack
{
	char data;
	struct PfStack *next;
} pfsnode;
pfsnode *pstop = NULL; // global struct
int IsEmpty(pfsnode *st)
{
	return st ? 0 : 1;
}
int IsFull()
{
	int r;
	pfsnode *t;
	t = (pfsnode *)malloc(sizeof(pfsnode));
	r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
	free(t);
	return r;
}
void ppush(pfsnode *st, char x)
{
	if (IsFull())
	{
		printf("Stack Overflow!");
		return;
	}
	pfsnode *t;
	t = (pfsnode *)malloc(sizeof(pfsnode));
	t->data = x;
	t->next = st;
	pstop = t;
}
char ppop(pfsnode *st)
{
	char x = ' ';
	if (IsEmpty(st))
	{
		printf("Stack Underflow!\n");
	}
	else
	{
		pstop = pstop->next;
		x = st->data;
	}
	return x;
}
void killps(pfsnode *st)
{
	if (!st)
		return;
	while (st)
	{
		ppop(st);
	}
}

//#####################################################################################################################################################
//
//#####################################################################################################################################################

// Evaluation Stack
// linked representation of stack for evaluation of the expression
// this stack will only store the addr of the tree nodes

typedef struct evalStack
{
	struct evalStack *next;
	node *addr;
} esnode;
esnode *estop = NULL; // global ptr

int isFull() // checks if heap is full
{
	esnode *temp;
	if (!(temp = (esnode *)malloc(sizeof(esnode))))
		return 1;
	free(temp);
	return 0;
}

int isEmpty(esnode *estop)
{
	if (!estop)
		return 1;
	return 0;
}

void push(esnode *currTop, node *addr)
{
	if (isFull())
		return;
	esnode *t = (esnode *)malloc(sizeof(node));
	t->addr = addr;
	t->next = currTop;
	currTop = t;
	return;
}
node *pop(esnode *currTop)
{
	if (isEmpty(currTop))
		return NULL;
	esnode *temp = currTop;
	node *x = currTop->addr;
	currTop = currTop->next;
	free(temp);
	return x;
}
int isOperator(char x)
{
	if (x != '+' && x != '-' && x != '*' && x != '/')
		return 0;
	return 1;
}
int isOperand(char x)
{
	if (x >= '0' && x <= '9')
		return 1;
	return 0;
}
int precedance(char operator)
{
	if (isOperator(operator))
	{
		if (operator== '+' || operator== '-')
			return 1;
		if (operator== '*' || operator== '/')
			return 2;
	}
	return -1;
}
void killes(esnode *st)
{
	if (!st)
		return;
	while (st)
	{
		pop(st);
	}
}

//#####################################################################################################################################################
//
//#####################################################################################################################################################

// Helper function to create a new node for tree
node *newNode(const char c)
{
	node *temp = NULL;
	temp = (node *)malloc(sizeof(node));
	temp->character = c;
	temp->right = temp->left = NULL;
	return temp;
}

// function to get the expression from user in infix form
void getExp(void)
{
	char x;
	int size = 0;
	printf("Enter Expression in Infix Form:\n");
	while ((x = getc(stdin)) != '\n') // get the input ignoring the whitespaces
	{
		if (x == ' ')
			;
		else
		{
			if (!(infix = (char *)realloc(infix, ++size)))
				return;
			infix[size - 1] = x;
		}
	}
	// terminate the string with null zero
	if (!(infix = (char *)realloc(infix, ++size)))
		return;
	infix[size - 1] = '\0';
	if (isValid(infix)) // convert given strig into postfix string if its valid
	{
		infix2postfix(infix);
	}
	else
	{
		free(infix);
		printf("Invalid Expression, Try Again!\n");
		getExp();
	}
	return;
}

// check if the expression in stdin in valid or not
int isValid(const char *exprn)
{
	int len = strlen(exprn);
	//corner case check if first or last char is operator
	if(isOperator(exprn[0])||isOperator(exprn[len-1]))
		return 0;
	// check for any different character than whitespace, operators and oprands
	for (int i = 0; i < len; i++)
	{
		if (!isOperand(exprn[i]) && !isOperator(exprn[i]))
		{
			return 0;
		}
	}
	// checks for successive operators or operands eg. +-, 12
	for (int i = 0; i < len - 1; i++)
	{
		if (
			(isOperand(exprn[i]) && isOperand(exprn[i + 1])) ||
			(isOperator(exprn[i]) && isOperator(exprn[i + 1])))
			return 0;
	}
	return 1;
}
// infix to postfix conversion
void infix2postfix(const char *infix)
{ // convert stack data into char
	int i, j;
	i = j = 0;
	postfix = (char *)malloc(sizeof(char) * (strlen(infix) + 2)); // 2 more cells to store null char and dummy char
	ppush(pstop, 'x');											  // dummy char will be ignored at time of flushing out the stack
	while (infix[i] != '\0')
	{
		if (isOperand(infix[i]))
			postfix[j++] = infix[i++];
		else
		{
			if (precedance(infix[i]) > precedance(pstop->data))
				ppush(pstop, infix[i++]);
			else
			{
				postfix[j++] = ppop(pstop);
			}
		}
	}
	while (pstop)
	{
		char temp;
		if ((temp = ppop(pstop)) == 'x') // if dummy char at last is popped then set postfix[j] with null char
			temp = '\0';
		postfix[j++] = temp;
	}
	killps(pstop);
	return;
}
// convert postfix expression into expression tree
void postfix2exp(EXP *root, const char *pf)
{
	char c;
	node *temp = NULL;
	node *a = NULL, *b = NULL;
	for (int i = 0; pf[i] != '\0'; i++) // scan each element of postfix expression
	{
		c = pf[i];
		temp = newNode(c);
		if (isOperand(c))//push if operand 
			petspush(top, temp);
		else if (isOperator(c))//pop last two values and set them as childs of temp, push temp
		{
			b = petspop(top);
			a = petspop(top);
			temp->left=a;
			temp->right=b;
			petspush(top, temp);
		}
	}
	//tree is created root node is at top of stack 
	*root=petspop(top);
	killpets(top);
	return;
}

//#####################################################################################################################################################
//
//#####################################################################################################################################################

//1. InitTree(): This function creates a new expression tree and populates is using an infix
// expression read from user. It should appropriately handle errors in the input.
void initTree(EXP *tree)
{
	*tree = NULL;
	getExp();
	postfix2exp(tree, postfix);
	return;
}
// 2. Traverse(): This function performs in-order traversal of the tree.
void Traverse(EXP tree)
{
	if(tree)
	{
		Traverse(tree->left);
		printf("%c",tree->character);
		Traverse(tree->right);
	}
	return;
}
// 3. Compute(): This function evaluates each subtree and displays the in-order traversal of
// intermediate tree created in the process. It returns the final result of the evaluation of the
// expression.
float Compute(EXP tree)
{
	if(tree)
	{
		int ans;
		char c;
		int a,b;
		c=tree->character;
		if(isOperand(c))
			return atoi(&c);
		else
			a=Compute(tree->left);
			b=Compute(tree->right);
			if(c=='+')
				ans=a+b;
			else if(c=='-')
				ans=a-b;
			else if(c=='*')
				ans=a*b;
			else if(c=='/')
				ans=a/b;
			printf("Computing:	%d %c %d\n",a,c,b);
			return ans;
	}
}
