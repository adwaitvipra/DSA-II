#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <limits.h>

#define MAX_SIZE 100
char *infix = NULL, *postfix = NULL; // global char ptrs
// Expression Tree Node Struct
typedef struct treeNode
{
	char *character;
	struct treeNode *left, *right;
} node;
typedef node *EXP;

// Infix to Postfix Stack
// array representation of stack for infix to postfix
typedef struct postStack
{
	char data;
	struct postStack* next;
} pfs;
pfs*pstop=NULL; // global struct
int IsEmpty(pfs *st)
{
    return st ? 0 : 1;
}
int IsFull()
{
    int r;
    pfs *t;
    t = (pfs *)malloc(sizeof(pfs));
    r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
    free(t);
    return r;
}
void ppush(pfs *st, char x)
{
    if (IsFull())
    {
        printf("Stack Overflow!");
        return;
    }
    pfs *t;
    t = (pfs *)malloc(sizeof(pfs));
    t->data = x;
    t->next = st;
    pstop = t;
}
char ppop(pfs *st)
{
    char x =' ';
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
// Evaluation Stack
// linked representation of stack for evaluation of the expression
// this stack will only store the addr of the tree nodes
typedef struct stackNode
{
	struct stackNode *next;
	node *addr;
} snode;
snode *evalTop = NULL; // global ptr

int isFull() // checks if heap is full
{
	snode *temp;
	if (!(temp = (snode *)malloc(sizeof(snode))))
		return 1;
	free(temp);
	return 0;
}

int isEmpty(snode *estop)
{
	if (!estop)
		return 1;
	return 0;
}

void push(snode *currTop, node *addr)
{
	if (isFull())
		return;
	snode *t = (snode *)malloc(sizeof(node));
	t->addr = addr;
	t->next = currTop;
	currTop = t;
	return;
}
node *pop(snode *currTop)
{
	if (isEmpty(currTop))
		return NULL;
	snode *temp = currTop;
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
int isValid(const char *exprn)
{
	int len = strlen(exprn);
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
	postfix = (char *)malloc(sizeof(char) * (strlen(infix) + 1));
	ppush(pstop, ' ');
	while (infix[i] != '\0')
	{
		if (isOperand(infix[i]))
			postfix[j++] = infix[i++];
		else
		{
			if (precedance(infix[i]) > precedance(pstop->data))
				push(pstop, infix[i++]);
			else
			{
				postfix[j++] = pop(pstop);
			}
		}
	}
	while (pstop != NULL)
	{
		postfix[j++] = pop(pstop);
	}
	postfix[j] = '\0';
	return;
}
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
			realloc(infix, ++size);
			infix[size - 1] = x;
		}
	}
	// terminate the string with null zero
	realloc(infix, ++size);
	infix[size - 1] = '\0';
	if (isValid(infix)) // convert given strig into postfix string if its valid
	{
		infix2postfix(infix);
	}
	else
	{
		free(infix);
	}
	return;
}

void initTree(EXP *tree)
{
	*tree = NULL;
	return;
}
node *createTree(EXP tree)//create expression tree from the infix and postfix
{

}
int main()
{
	EXP t;
	getExp();
	puts(infix);
	puts(postfix);
	return 0;
}
