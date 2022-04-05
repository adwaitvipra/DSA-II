typedef struct Node // creating a struct for node
{
    int mis;
    char *name;
    struct Node *left, *right;
} node;

typedef node *bst; // typecasting a ptr to node as bst

void initBST(bst *t)
{
    *t = NULL;
    return;
}
void insertNode(bst *t, int x, char *n)
{
    node *nn = NULL;
    nn = (node *)malloc(sizeof(node));

    if (!nn)
    {
        free(nn);
        printf("Overflow!\n");
        return;
    }

    nn->mis = x;
    nn->name = n;
    nn->left = nn->right = NULL;

    node *p, *q; // q is a trailing ptr of
    p = *t;
    q = NULL;

    if (!p)
    {
        *t = p;
        return;
    }

    while (p) // move p until it becomes null
    {
        if (p->mis == x)
        {
            printf("Duplicate Entry!\n");
            return;
        }

        q = p; // let q follow p
        if (p->mis < x)
            p = p->right;
        else
            p = p->left;
    }

    if (q->mis < x)
        q->right = nn;
    else
        q->left = nn;
    return;
}
int removeNode(bst *t, int key)
{
    return;
}
int search(bst t, int key)
{
    return;
}
void postOrder(bst t) // left right vlaue
{
    return;
}
void displayLevel(bst t, int level)
{
    return;
}
void destroyTree(bst *t)
{
    return;
}