#ifndef GRAPH_H
#define GRAPH_H
#define MAX 1024
typedef struct GraphNode
{
    int vertex;
    int weight;
    struct GraphNode *next;
} node;
typedef struct graph
{
    node **A;
    int V;
    int E;
} graph;

void initGraph(graph *, char *);
void printGraph(graph *);
int inDegree(graph *, int);
int outDegree(graph *, int);

#endif