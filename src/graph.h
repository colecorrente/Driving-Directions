/**
 * This header provides the functions for working with our graph ADT.
 * Run time are provided in the comments of the functions
 *
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Typedef to make function signatures clearer.
typedef unsigned long vertex_t;
// Forward declaration of the graph type.
typedef struct graph graph;

/**
 * Creates a new graph with V = {0,1,2,...,n-1} and E={}.
 *
 * The set of vertices are fixed throughout the life of the graph.
 *
 * @param  n the number of vertices
 * @return   a new graph
 */
graph* graph_create(size_t n, bool directed);

/**
 * Deallocates all memory associated with a graph.
 *
 * @param self the graph being deallocated.
 */
void graph_destroy(graph* self);

/**
 * Returns the number of vertices in a graph.
 *
 * Runtime: O(1)
 *
 * @param  self the graph being queried
 * @return      the number of vertices
 */
size_t graph_vertex_count(graph* self);

/**
 * Returns the number of edges in a graph.
 *
 * Runtime: O(1)
 *
 * @param  self the graph being queried
 * @return      the number of vertices
 */
size_t graph_edge_count(graph* self);

/**
 * Returns the directedness of a graph.
 *
 * Runtime: O(1)
 *
 * @param  self the graph being queried
 * @return      true if the graph is directed and false if it is undirected
 */
bool graph_directed(graph* self);

/**
 * Determines if there is an edge between two vertices.
 *
 * Runtime: O(n) or more accurately O(deg(u))
 *
 * @param  self the graph being queried
 * @param  u    source vertex
 * @param  v    destination vertex
 * @param[out]  has_edge  assigned true if edge u->v exists and false otherwise
 * @pre         u and v are valid vertices for self
 * @return      self if preconditions are met and NULL otherwise
 */
graph* graph_edge(graph* self, vertex_t u, vertex_t v, bool* has_edge);

/**
 * Determines the (out) degree of a vertex.
 *
 * Runtime: O(1)
 *
 * @param  self the graph being queried
 * @param  u    the vertex being queried
 * @param  deg[out]  assigned the degree of u in self
 * @pre         u is a valid vertex for self
 * @return      self if preconditions are met and NULL otherwise
 */
graph* graph_degree(graph* self, vertex_t u, size_t* deg);

/**
 * Determines the (outgoing) neighbors of a vertex.
 *
 * Runtime: O(n)
 *
 * Warning: The array vs must be of size at least deg(u).
 *
 * @param  self the graph being queried
 * @param  u    a source vertex
 * @param  vs[out]  assigned the neighbors of u
 * @pre         u is a valid vertex for self
 * @return      self if preconditions are met and false otherwise
 */
graph* graph_neighbors(graph* self, vertex_t u, vertex_t* vs);

/**
 * Adds an edge to a graph.
 *
 * Runtime: O(n)
 *
 * Note: If the edge being added is already in the graph, no action is performed.
 *
 * @param  self the graph being modified
 * @param  u    the source vertex
 * @param  v    the destination vertex
 * @pre         u and v are valid vertices for self
 * @return      self if preconditions are met and false otherwise
 */
graph* graph_add_edge(graph* self, vertex_t u, vertex_t v);

/**
 * Removes an edge from a graph.
 *
 * Runtime: O(n)
 *
 * Note: If the edge being removed is not in the graph, no action is performed.
 *
 * @param  self the graph being modified
 * @param  u    the source vertex
 * @param  v    the destination vertex
 * @pre         u and v are valid vertices for self
 * @return      self if preconditions are met and false otherwise
 */
graph* graph_remove_edge(graph* self, vertex_t u, vertex_t v);

// Note: The following method was used for testing, but is not part of the API.
void graph_write(graph* self, FILE* stream);

#endif//__GRAPH_H__
