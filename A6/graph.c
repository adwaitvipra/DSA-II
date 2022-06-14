#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

//##########################################################################################################################
//                                                  Stack
//##########################################################################################################################
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} snode;
snode *top = NULL;
int isEmptyStk(snode *st)
{
    return st ? 0 : 1;
}
int isFullStk()
{
    int r;
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
    free(t);
    return r;
}
char StackTop(snode *st)
{
    if (st)
        return st->data;
    return -1;
}
void push(snode *st, int x)
{
    if (isFullStk())
    {
        printf("Stack Overflow!");
        return;
    }
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    t->data = x;
    t->next = st;
    top = t;
}
int pop(snode *st)
{
    int x = -1;
    if (isEmptyStk(st))
    {
        printf("Stack Underflow!\n");
    }
    else
    {
        top = top->next;
        x = st->data;
    }
    return x;
}
int peek(snode *st, int index)
{
    int i;
    if (isEmptyStk(st)) // return -1 when stack is empty
        return -1;
    for (i = 0; i < index - 1 && st; i++) // move st until it reaches on index or st is is not null
        st = st->next;
    return st->data;
}
void KillStack(snode *st)
{
    if (!st)
        return;
    while (st)
    {
        pop(st);
    }
}
//##########################################################################################################################
//                                                  Queue
//##########################################################################################################################
typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
} qnode;
qnode *front = NULL, *rear = NULL;
int isEmptyQ()
{
    if (front == NULL)
        return 1;
    return 0;
}
int isFullQ()
{
    qnode *t;
    t = (qnode *)malloc(sizeof(qnode));
    if (!t)
        return 1;
    free(t);
    return 0;
}

void enqueue(int x)
{
    if (isFullQ())
    {
        printf("Queue Overflow!\n");
        return;
    }
    else
    {
        qnode *t;
        t = (qnode *)malloc(sizeof(qnode));
        t->data = x;
        t->next = NULL;
        if (front == NULL)
            front = rear = t;
        else
        {
            rear->next = t;
            rear = t;
        }
    }
}
int dequeue()
{
    int x = -1;
    if (isEmptyQ())
    {
        printf("Queue Underflow!\n");
        return x;
    }
    else
    {
        qnode *p;
        p = front;
        front = front->next;
        x = p->data;
        free(p);
    }
    return x;
}
void destroyQ()
{
    while (!isEmptyQ())
        dequeue();
} //##########################################################################################################################
//                                                      Heap
//##########################################################################################################################
// Min Heap
typedef struct
{
    edge *H;
    int size;
    int length;
} heap;
int isFull(heap *);
int isEmpty(heap *);
void initHeap(heap *, int);
void insert(heap *, edge);
edge returnMin(heap *);
void heapify(heap *, int);
void adjust(heap *);

void swap(edge *a, edge *b)
{
    edge temp = *a;
    *a = *b;
    *b = temp;
    return;
}
int isFull(heap *h)
{
    if (h->length == h->size - 1)
        return 1;
    return 0;
}
int isEmpty(heap *h)
{
    if (h->length == -1)
        return 1;
    return 0;
}
void initHeap(heap *h, int s)
{
    h->H = (edge *)malloc(sizeof(edge) * s);
    h->size = s;
    h->length = -1;
    return;
}

void insert(heap *h, edge x)
{
    // 1. Check if given heap is full.
    // 2. If not full then increment length and insert new value at length th index in heap.
    // 3. Now heapify until child is in rule (min/max) and parent is greater than root (0)

    if (isFull(h))
        return;
    int child = ++h->length;
    h->H[child] = x;
    heapify(h, child);
    return;
}
edge returnMin(heap *h)
{
    // 1. check if given heap is empty.
    // 2. if not empty then return the rule ele (min/max), swap 0th ele with h.length th ele and decrement length
    // 3. adjust the heap i.e. heapify from top to down
    edge x = {-1, -1, -1};
    if (isEmpty(h))
        return x;
    x = h->H[0];
    swap(&h->H[0], &h->H[h->length--]);
    adjust(h);
    return x;
}

void heapify(heap *h, int child)
{
    int parent = (child - 1) / 2;
    int n = h->H[child].weight;
    int pn = h->H[parent].weight;

    if (n < pn && (parent >= 0 && child <= h->length))
    {
        swap(&h->H[child], &h->H[parent]);
        heapify(h, parent);
    }
    return;
}
void adjust(heap *h)
{
    int parent = 0;
    int min;

    while (parent <= h->length)
    {
        int lc = parent * 2 + 1;
        int rc = parent * 2 + 2;
        int ln = h->H[lc].weight;
        int rn = h->H[rc].weight;

        if (lc <= h->length)
        {
            if (rc <= h->length) // right child exists
            {
                if (ln >= rn) // left node is greater than or equal to right node
                    min = rc;
                else // right node is greater than left node
                    min = lc;
            }
            else // only left child exists
                min = lc;

            if (h->H[parent].weight > h->H[min].weight)
            {
                swap(&h->H[parent], &h->H[min]);
                parent = min;
            }
            else
                return;
        }
        else // neither left nor right child exists
            return;
    }
    return;
}

void killHeap(heap *h)
{
    free(h->H);
    h->size = -1;
    h->length = 0;
    return;
}
//##########################################################################################################################
//                                           Graph Traversal Algorithms
//##########################################################################################################################
// Breadth First Search
void BFS(graph *g, int start)
{
    int x;
    node *ptr = NULL;
    int *visited = (int *)calloc(g->V, sizeof(int)); // init a visited arr with zeros
    enqueue(start);
    visited[start] = 1;
    printf("\n%d\n", start);
    while (!isEmptyQ())
    {
        x = dequeue();
        ptr = g->A[x];
        while (ptr)
        {
            if (!visited[ptr->vertex])
            {
                enqueue(ptr->vertex);
                visited[ptr->vertex] = 1;
                printf("%d\n", ptr->vertex);
            }
            ptr = ptr->next;
        }
    }
    free(visited);
    destroyQ();
    return;
}

// Depth First Search
void DFS(graph *g, int start)
{
    int x;
    node *ptr = NULL;
    int *visited = (int *)calloc(g->V, sizeof(int)); // init a visited arr with zeros
    push(top, start);
    visited[start] = 1;
    printf("\n%d\n", start);
    while (!isEmptyStk(top))
    {
        x = pop(top);
        ptr = g->A[x];
        while (ptr)
        {
            if (!visited[ptr->vertex])
            {
                push(top, ptr->vertex);
                visited[ptr->vertex] = 1;
                printf("%d\n", ptr->vertex);
            }
            ptr = ptr->next;
        }
    }
    KillStack(top);
    free(visited);
    return;
} //##########################################################################################################################
//                                         Shortest Path Algoritms
//##########################################################################################################################
//##########################################################################################################################
//                                          Minimum Spanning Tree
//##########################################################################################################################
// Prim's Algorithm
edge *Prims(graph *g)
{
    edge *edges = (edge *)malloc(sizeof(edge) * (g->V - 1));
    edge minEdge;
    heap minEdges;
    initHeap(&minEdges, g->V);

    int *iptr = NULL, minWt = INT_MAX;
    int *visited = (int *)calloc(g->V, sizeof(int));
    int *tree = (int *)calloc(g->V, sizeof(int));
    int *fringed = (int *)calloc(g->V, sizeof(int));
    int source, destination;
    source = 0;
    visited[source] = 1;
    tree[source] = 1;
    iptr = g->A[source];
    for (int i = 0; i < g->V - 1; i++)
    {
        while (iptr)
        {
            edge temp;
            if (!visited[iptr->vertex] && !fringed[iptr->vertex])
            {
                fringed[iptr->vertex] = 1;
                temp.src = source;
                temp.dest = iptr->vertex;
                temp.weight = iptr->weight;
                insert(&minEdges, temp);
            }
            iptr = iptr->next;
        }
    }

    return edges;
}
//##########################################################################################################################
//                                              Graph Supporting Algorithms
//##########################################################################################################################
int outDegree(graph *g, int v)
{
    node *ptr = g->A[v];
    int cnt = 0;
    while (ptr)
    {
        cnt++;
        ptr = ptr->next;
    }
    return cnt;
}
int inDegree(graph *g, int v)
{
    node *ptr;
    int cnt = 0;
    for (int i = 0; i < g->V; i++)
    {
        ptr = g->A[i];
        while (ptr)
        {
            if (ptr->vertex == v)
                cnt++;
            ptr = ptr->next;
        }
    }
    return cnt;
}
int getConnectedVertices(graph *g, int v)
{
    node *ptr = g->A[v];
    int cnto = 0;
    int cnti = 0;

    while (ptr)
    {
        cnto++;
        printf("%d ", ptr->vertex);
        ptr = ptr->next;
    }

    for (int i = 0; i < g->V; i++)
    {
        ptr = g->A[i];
        while (ptr)
        {
            if (ptr->vertex == v)
            {
                cnti++;
                printf("%d ", i);
            }
            ptr = ptr->next;
        }
    }
    return cnto + cnti;
}
int isDirected(graph *g) // returns 0 even if weights are different
{
    // checking if there exists a edge V--K for edge K--V, if not found then directed
    node *iptr, *jptr;
    for (int k = 0; k < g->V; k++)
    {
        iptr = g->A[k]; // K--V, Kth row -- Vth col
        while (iptr)
        {
            jptr = g->A[iptr->vertex]; // V--K, Vth row -- Kth col
            while (jptr)               // find K in Vth row
            {
                if (jptr->vertex == k) // if edge V--K found break
                    break;
                jptr = jptr->next;
            }
            if (!jptr) // if not found edge V--K then graph is directed
                return 1;
            iptr = iptr->next;
        }
    }
    return 0;
}
void initGraph(graph *g, char *filename)
{
    FILE *fh = fopen(filename, "r");
    int x;
    fscanf(fh, "%d", &g->V); // get vertices
    // malloc array of pointer to nodes
    g->A = (node **)malloc(sizeof(node *) * g->V);
    for (int i = 0; i < g->V; i++) // make the pointer as null
        g->A[i] = NULL;
    // read the data
    for (int j = 0; j < g->V; j++)
    {
        for (int i = 0; i < g->V; i++)
        {
            fscanf(fh, "%d", &x);
            if (x != 0)
            {
                node *t = (node *)malloc(sizeof(node));
                t->vertex = i;
                t->weight = x;
                t->next = g->A[j];
                g->A[j] = t;
            }
        }
    }
    fclose(fh);
    return;
}
void displayMatrix(graph *g)
{
    node *ptr;
    int **mat;
    mat = (int **)calloc((g->V), sizeof(int *));
    for (int x = 0; x < g->V; x++)
        mat[x] = (int *)calloc((g->V), sizeof(int));
    int i, j, k;
    for (i = 0; i < g->V; i++)
    {
        ptr = g->A[i];
        while (ptr)
        {
            mat[i][ptr->vertex] = ptr->weight;
            ptr = ptr->next;
        }
    }
    for (j = 0; j < g->V; j++)
    {
        for (k = 0; k < g->V; k++)
            printf("%d ", mat[j][k]);
        printf("\n");
    }
    free(mat);
    return;
}
int main(int argc, char const *argv[])
{
    graph g;
    initGraph(&g, "graph.txt");
    displayMatrix(&g);
    BFS(&g, 0);
    DFS(&g, 0);
    return 0;
}
