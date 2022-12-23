// Implement Graph using Adjacency List representation. Perform following operations:
// Initialize the graphs from a file name passed as command line argument.
// Display graph in matrix form.
// Perform BSF and DFS starting from a randomly selected vertex.
// Display degree of each vertex. For a directed Graph Display in-degree and out-
// degree of each node.
// Find the minimum spanning tree of an undirected weighted graph using any of the
// algorithms.
// Find shortest path between any two vertices using Dijkstra’s algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

int main(int argc, char const *argv[])
{
    graph gobj;
    initGraph(&gobj, "graph.txt");
    displayMatrix(&gobj);
    printf("\n\n");
    printf("%d is indegree\n", inDegree(&gobj, 0));
    printf("%d is outdegree\n", outDegree(&gobj, 0));
    printf("\n\n%d= is Directed\n", isDirected(&gobj));
    getConnectedVertices(&gobj, 0);
    edge *x = Prims(&gobj);
    for (int i = 0; i < (gobj.V - 1); i++)
    {
        printf("\n(%d,%d) = %d\n", x[i].src, x[i].dest, x[i].weight);
    }
    return 0;
}
