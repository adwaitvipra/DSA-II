#ifndef AVL_H
#define AVL_H
typedef struct Node
{
    char bf;
    char month[15];
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
} node;

typedef node *AVL; // ptr to the node
void initAVL(AVL *);
int insertNode(AVL *, const char *);
node* removeNode(AVL *, const char *);
void traverse(AVL);
void destroyTree(AVL *);
#endif
