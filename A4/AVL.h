#ifndef AVL_H
#define AVL_H
typedef struct Node
{
    struct Node *parent;
    char *monthName[15];
    struct Node *leftChild, *rightChild;
    char balanceFactor='0';
}node;
typedef node * AVL; //ptr to the node 

void initAVL(AVL *);
node* insertNode(AVL *, char *);
node* removeNode(AVL *, char *);
void traverse(AVL);
void destroyTree(AVL *);
#endif
