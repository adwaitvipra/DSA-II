// Implement Graph using Adjacency List representation. Perform following operations:
// Initialize the graphs from a file name passed as command line argument.
// Display graph in matrix form.
// Perform BSF and DFS starting from a randomly selected vertex.
// Display degree of each vertex. For a directed Graph Display in-degree and out-
// degree of each node.
// 5. Find the minimum spanning tree of an undirected weighted graph using any of the
// 2 algorithms.
// 6. Find shortest path between any two vertices using Dijkstra’s algorithm
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    graph g;
    initGraph(&g, "graph.txt");
    displayMatrix(&g);
    printf("Is Directed:%d\n", isDirected(&g));
    edge *x = Prims(&g);
    for (int i = 0; i < (g.V - 1); i++)
    {
        printf("\n(%d,%d) = %d\n", x[i].src, x[i].dest, x[i].weight);
    }
    return 0;
    return 0;
}
