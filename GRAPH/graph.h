#ifndef GRAPH_H
#define GRAPH_H
#define MAX 1024

typedef struct GraphNode
{
    int vertex;
    int weight;
    struct GraphNode *next;
} node;

typedef struct Edge
{
    int src, dest, weight;
} edge;

typedef struct graph
{
    node **A;
    int V;
    int E;
} graph;

void initGraph(graph *, char *);
bool isDirected(graph *gptr); 
int getConnectedVertices(graph *, int );
int outDegree(graph *, int );
int inDegree(graph *, int );
void displayMatrix(graph *);
void freeDisplayMatrix(int **, int);

void BFS(graph *, int );
void DFS(graph *, int );
edge *Prims(graph *);
void Dijkstra(graph *, int , int );

#endif
