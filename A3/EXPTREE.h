#ifndef EXPTREE_H
#define EXPTREE_H
#define MAX_SIZE 1024
// Structure Declarations
// Expression Tree Node Struct
typedef struct treeNode
{
    char character;
    struct treeNode *left, *right;
} node;
typedef node *EXP;
// postfix stack node struct
typedef struct PfStack
{
    char data;
    struct PfStack *next;
} pfsnode;
// postfix to expression tree stack node struct
typedef struct PfEtStack
{
    node *x;
    struct PfEtStack *next;
} petsnode;
// function prototypes
void initTree(EXP *);
void Traverse(EXP);
float Compute(EXP);

#endif