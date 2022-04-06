typedef struct Node // creating a struct for node
{
    int mis;
    char *name;
    struct Node *left, *right;
} node;

typedef node *bst; // typecasting a ptr to node as bst

struct StackNode
{
    node *x;
    struct StackNode *next;
};