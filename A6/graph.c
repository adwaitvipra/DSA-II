#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
//##########################################################################################################################
//                                                  Graph
//##########################################################################################################################
//##########################################################################################################################
//                                                  Graph
//##########################################################################################################################
//##########################################################################################################################
//                                                  Graph
//##########################################################################################################################
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
    else
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
}
//##########################################################################################################################
//                                                  Graph
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
}
int main(int argc, char const *argv[])
{
    graph g;
    initGraph(&g, "graph.txt");
    printf("%d %d\n", inDegree(&g, 7), outDegree(&g, 7));
    printf("%d \n", getConnectedVertices(&g, 7));
    printf("%d \n", isDirected(&g));
    return 0;
}
