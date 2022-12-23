#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

bool isEmptyStk(void)
{
    return top ? false : true; 
}

bool isFullStk(void)
{
    snode *tmpNode=NULL;
 
    if(!(tmpNode = (snode *)malloc(sizeof(snode))))
	    return true;
    free(tmpNode);

    return false;
}

int stackTop(void)
{
    if (top)
        return top->data;
    return INT_MIN;
}

void push(int val)
{
	snode *newNode=NULL;
    if (isFullStk())
        printf("Stack Overflow!");
    else
    {
   	newNode = (snode *)malloc(sizeof(snode));
    	newNode->data = val;
    	newNode->next = top;
    	top = newNode;
    }
    return;
}

int pop(void)
{
    int val = INT_MIN;
    snode *tmp = NULL;

    if (isEmptyStk())
        printf("Stack Underflow!\n");
    else
    {
	tmp = top;
        val = tmp->data;
        top = top->next;
	free(tmp);
    }
    return val;
}

int peek(int index)
{
    snode *sptr = NULL;

    if (isEmptyStk()) 
        return INT_MIN;

    for (int i = 0; i < index - 1 && sptr; i++) // move ptr until it reaches on index or ptr is is not null
        sptr = sptr->next;

    return sptr->data;
}

void killStack(void)
{
    while (top)
        pop();
    return ;
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

bool isEmptyQ(void)
{
    if (!front) 
        return true;
    return false;
}

bool isFullQ(void)
{
    qnode *tmpNode=NULL;
    if(!(tmpNode = (qnode *)malloc(sizeof(qnode))))
	    return true;
    free(tmpNode);
    return false;
}

void enqueue(int val)
{
    qnode *newNode = NULL;
    if (isFullQ())
        printf("Queue Overflow!\n");
    else
    {
        if(!(newNode = (qnode *)malloc(sizeof(qnode))))
		return ;
        newNode->data = val;
        newNode->next = NULL;

        if (!front)
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    return ;
}

int dequeue(void)
{
    int val = INT_MIN;
    qnode *tmp=NULL;
    if (isEmptyQ())
        printf("Queue Underflow!\n");
    else
    {
        tmp = front;
        front = front->next;
        val = tmp->data;
        free(tmp);
    }
    return val;
}

void destroyQ(void)
{
    while (!isEmptyQ())
        dequeue();
    return ; 
}
//##########################################################################################################################
//                                                      Heap
//##########################################################################################################################
// Min Heap
typedef struct
{
    edge *H;
    int size;
    int length;
} heap;

bool isFullHeap(heap *);
bool isEmptyHeap(heap *);
void initHeap(heap *, int);
void insertHeap(heap *, edge);
edge returnMinHeap(heap *);
void heapify(heap *, int);
void adjust(heap *);

void swap(edge *a, edge *b)
{
    edge temp = *a;
    *a = *b;
    *b = temp;
    return;
}

bool isFullHeap(heap *hptr)
{
    if (hptr->length == hptr->size - 1)
        return true;
    return false;
}

bool isEmptyHeap(heap *hptr)
{
    if (hptr->length == -1)
        return true;
    return false;
}

void initHeap(heap *hptr, int size)
{
    hptr->H = NULL;
    if(!(hptr->H = (edge *)malloc(sizeof(edge) * size)))
	    return;
    hptr->size = size;
    hptr->length = -1;
    return;
}

void insertHeap(heap *hptr, edge eobj)
{
    // 1. Check if given heap is full.
    // 2. If not full then increment length and insert new value at length th index in heap.
    // 3. Now heapify until child is in rule (min/max) and parent is greater than root (0)

	int child;
    if (isFullHeap(hptr))
        return;
    child = ++hptr->length;
    hptr->H[child] = eobj;
    heapify(hptr, child);
    return;
}

edge returnMinHeap(heap *hptr)
{
    // 1. check if given heap is empty.
    // 2. if not empty then return the rule ele (min/max), swap 0th ele with h.length th ele and decrement length
    // 3. adjust the heap i.e. heapify from top to down

    edge eobj = {-1, -1, -1};
    if (isEmptyHeap(hptr))
        return eobj;
    eobj = hptr->H[0];
    swap(&(hptr->H[0]), &(hptr->H[hptr->length--]));
    adjust(hptr);
    return eobj;
}

void heapify(heap *hptr, int child)
{
    int parent = (child - 1) / 2;
    int childNode = hptr->H[child].weight;
    int parentNode = hptr->H[parent].weight;

    if ((childNode < parentNode) && (parent >= 0 && child <= hptr->length))
    {
        swap(&(hptr->H[child]), &(hptr->H[parent]));
        heapify(hptr, parent);
    }
    return;
}

void adjust(heap *hptr)
{
    int parent = 0;
    int min;
    int leftChild, rightChild, leftNode, rightNode;

    while (parent <= hptr->length)
    {
        leftChild = parent * 2 + 1;
        rightChild = parent * 2 + 2;
        leftNode = hptr->H[leftChild].weight;
        rightNode = hptr->H[rightChild].weight;

        if (leftChild <= hptr->length)
        {
            if (rightChild <= hptr->length) // right child exists
            {
                if (leftNode >= rightNode) // left node is greater than or equal to right node
                    min = rightChild;
                else // right node is greater than left node
                    min = leftChild;
            }
            else // only left child exists
                min = leftChild;

            if (hptr->H[parent].weight > hptr->H[min].weight)
            {
                swap(&(hptr->H[parent]), &(hptr->H[min]));
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

void killHeap(heap *hptr)
{
    free(hptr->H);
    hptr->size = -1;
    hptr->length = 0;
    return;
}
//##########################################################################################################################
//                                           Graph Traversal Algorithms
//##########################################################################################################################
// Breadth First Search
void BFS(graph *gptr, int start)
{
    int vtx, *visited = NULL;
    node *nptr = NULL;

    if(!(visited = (int *)calloc(gptr->V, sizeof(int)))) // init a visited arr with zeros
	    return ; 

    enqueue(start);
    visited[start] = 1;
    printf("\n%d\n", start);

    while (!isEmptyQ())
    {
        vtx = dequeue();
        nptr = gptr->A[vtx];
        while (nptr)
        {
            if (!visited[nptr->vertex])
            {
                enqueue(nptr->vertex);
                visited[nptr->vertex] = 1;
                printf("%d\n", nptr->vertex);
            }
            nptr = nptr->next;
        }
    }
    free(visited);
    destroyQ();
    return;
}

// Depth First Search
void DFS(graph *gptr, int start)
{
    int vtx, *visited = NULL;
    node *nptr = NULL;
    if (!(visited = (int *)calloc(gptr->V, sizeof(int))))
	    return ; // init a visited arr with zeros
    push(start);
    visited[start] = 1;
    printf("\n%d\n", start);
    while (!isEmptyStk())
    {
        vtx = pop();
        nptr = gptr->A[vtx];
        while (nptr)
        {
            if (!visited[nptr->vertex])
            {
                push(nptr->vertex);
                visited[nptr->vertex] = 1;
                printf("%d\n", nptr->vertex);
            }
            nptr = nptr->next;
        }
    }
    killStack();
    free(visited);
    return;
}
//##########################################################################################################################
//                                         Shortest Path Algorithms
//##########################################################################################################################
// Dijkstra's Algorithm
void Dijkstra(graph *gptr, int start, int end)
{
    return;
}
//##########################################################################################################################
//                                          Minimum Spanning Tree
//##########################################################################################################################
// Prim's Algorithm
edge *Prims(graph *gptr)
{
    edge etmp, *mst = NULL;
    int curr = 0, *visited = NULL;
    node *iptr;

    if(!(mst = (edge *)malloc(sizeof(edge) * (gptr->V - 1))))
	   return NULL;
    if(!(visited = (int *)calloc(gptr->V, sizeof(int))))
	    return NULL;

    visited[curr] = 1;
    iptr = gptr->A[curr];

    heap minEgdes;
    initHeap(&minEgdes, gptr->V);

    for (int i = 0; i < gptr->V - 1; i++)
    {
        while (iptr)
        {
            if (visited[curr] && !visited[iptr->vertex])
            {
                etmp.src = curr;
                etmp.dest = iptr->vertex;
                etmp.weight = iptr->weight;
                insertHeap(&minEgdes, etmp);
            }
            iptr = iptr->next;
        }
        mst[i] = returnMinHeap(&minEgdes);
        curr = mst[i].dest;
        visited[curr] = 1;
        iptr = gptr->A[curr];
    }
    killHeap(&minEgdes);
    return mst;
}
// Kruskal's Algorithm

//##########################################################################################################################
//                                              Graph Supporting Algorithms
//##########################################################################################################################

int outDegree(graph *gptr, int vtx)
{
    int cnt = 0;
    node *nptr = NULL;

    nptr = gptr->A[vtx];

    while (nptr)
    {
        cnt++;
        nptr = nptr->next;
    }
    return cnt;
}

int inDegree(graph *gptr, int vtx)
{
    node *nptr = NULL;
    int cnt = 0;

    for (int i = 0; i < gptr->V; i++)
    {
        nptr = gptr->A[i];
        while (nptr)
        {
            if (nptr->vertex == vtx)
                cnt++;
            nptr = nptr->next;
        }
    }
    return cnt;
}

int getConnectedVertices(graph *gptr, int vtx)
{
    node *nptr = NULL;
    int cnto = 0;
    int cnti = 0;

    nptr = gptr->A[vtx];

    while (nptr)
    {
        cnto++;
        printf("%d ", nptr->vertex);
        nptr = nptr->next;
    }

    for (int i = 0; i < gptr->V; i++)
    {
        nptr = gptr->A[i];
        while (nptr)
        {
            if (nptr->vertex == vtx)
            {
                cnti++;
                printf("%d ", i);
            }
            nptr = nptr->next;
        }
    }
    return cnto + cnti;
}

bool isDirected(graph *gptr) // returns false even if weights are different
{
    // checking if there exists a edge V--K for edge K--V, if not found then directed
    node *iptr, *jptr;
    for (int k = 0; k < gptr->V; k++)
    {
        iptr = gptr->A[k]; // K--V, Kth row -- Vth col
        while (iptr)
        {
            jptr = gptr->A[iptr->vertex]; // V--K, Vth row -- Kth col
            while (jptr)               // find K in Vth row
            {
                if (jptr->vertex == k) // if edge V--K found break
                    break;
                jptr = jptr->next;
            }
            if (!jptr) // if not found edge V--K then graph is directed
                return true;
            iptr = iptr->next;
        }
    }
    return false;
}

void initGraph(graph *gptr, char *filename)
{
    int x;
    node *tmpNode = NULL;
    FILE *fh = fopen(filename, "r");

    fscanf(fh, "%d", &(gptr->V)); // get vertices
    // malloc array of pointer to nodes
    gptr->A = (node **)malloc(sizeof(node *) * gptr->V);
    for (int i = 0; i < gptr->V; i++) // make the pointer as null
        gptr->A[i] = NULL;
    // read the data
    for (int j = 0; j < gptr->V; j++)
    {
        for (int i = 0; i < gptr->V; i++)
        {
            fscanf(fh, "%d", &x);
            if (x != 0)
            {
                tmpNode = (node *)malloc(sizeof(node));
                tmpNode->vertex = i;
                tmpNode->weight = x;
                tmpNode->next = gptr->A[j];
                gptr->A[j] = tmpNode;
            }
        }
    }
    fclose(fh);
    return;
}

void displayMatrix(graph *gptr)
{
    node *nptr = NULL;
    int **matrix = NULL;
    int i, j, k;
 
    if(!(matrix = (int **)calloc((gptr->V), sizeof(int *))))
	    return ;

    for (int x = 0; x < gptr->V; x++)
    {
        if(!(matrix[x] = (int *)calloc((gptr->V), sizeof(int))))
	{
		freeDisplayMatrix(matrix, x);
		return ;
	}
    }

    for (i = 0; i < gptr->V; i++)
    {
        nptr = gptr->A[i];
        while (nptr)
        {
            matrix[i][nptr->vertex] = nptr->weight;
            nptr = nptr->next;
        }
    }

    for (j = 0; j < gptr->V; j++)
    {
        for (k = 0; k < gptr->V; k++)
            printf("%d ", matrix[j][k]);
        printf("\n");
    }
    freeDisplayMatrix(matrix, gptr->V);
    return;
}

void freeDisplayMatrix(int **matrix, int size)
{
	if(matrix)
	{
		for(int i=0; i<size; i++)
			if(matrix[i])
				free(matrix[i]);
		free(matrix);
	}
	return ;
}

