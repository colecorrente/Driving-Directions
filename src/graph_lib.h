#ifndef __GRAPH_LIB_H__
#define __GRAPH_LIB_H__

#include "graph.h"

/**
* Takes an input graph and produces a new graph with all edge directions reversed.
*
* Note: The returned graph is a NEW graph. Do not modify the orginal graph!
*
* @param  G input graph
* @return   new graph with reversed edges.
*/
graph* graph_edge_reversal(graph* G);

/**
* Performs a BFS without restart.
*
* The output of this search is an array of parent indexies. The start vertex
* and any vertices not reachable by the search should be considered their own
* parent.
*
* @param G      the graph to search
* @param start  vertex to start the search with
* @param parent[out] the output array of parents
*/
void graph_bfs(graph* G, vertex_t start, vertex_t* parent);

/**
* determines weather a graph is connected
*
* @param  G the graph to test
* @return   boolean. true if connected, false if not connected
*/
bool graph_is_connected(graph* G);

/**
* dijkstras algorithm for finding the shortest path in the map. This function returns the list of parents which represnt the shortest paths.
*
* @param G           the graph to search
* @param start       the starting vertext
* @param parent[out] the output array of parents
* @param edge_length the 2D array of edge_lengths (weights) for the graph to determine the shortest path.
*/
void graph_dijkstras(graph* G, vertex_t start, vertex_t* parent, double** edge_length);

/**
* Take the list of parents from disjkstras algorithm and traverse the list given a start and end vertex, resulting in a final list of shortest path.
*
* @param parent    the parent array outputed from disjkstras
* @param start     the starting vertex of the path
* @param end       the ending vertext of the path
* @param path[out] the shortest path
* @param path_size the size of the shortest path
*/
void graph_traverse_parents(vertex_t* parent, vertex_t start, vertex_t end,vertex_t* path, int* path_size);

#endif//__GRAPH_LIB_H__
