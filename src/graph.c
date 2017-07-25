// Implementations of the function declarations in graph.h.
#include "graph.h"
#include <assert.h>

struct graph {
    size_t n;
    size_t m;
    bool directed;
    vertex_t** adj_list;
    size_t* degree;
};

graph* graph_create(size_t n, bool directed) {
    graph* new_graph = malloc(sizeof(graph));

    new_graph->n = n;
    new_graph->m = 0;
    new_graph->directed = directed;

    new_graph->adj_list = malloc(n * sizeof(vertex_t*));
    for (size_t i = 0; i < n; i++) {
        new_graph->adj_list[i] = malloc(n * sizeof(vertex_t));
    }

    new_graph->degree = malloc(n * sizeof(size_t));
    for (size_t i = 0; i < n; i++) new_graph->degree[i] = 0;

    return new_graph;
}

void graph_destroy(graph* self) {
    free(self->degree);
    for (size_t i = 0; i < self->n; i++) free(self->adj_list[i]);
    free(self->adj_list);
    free(self);
}

size_t graph_vertex_count(graph* self) {
    return self->n;
}

size_t graph_edge_count(graph* self) {
    if (self->directed) {
        return self->m;
    } else { // Undirected graphs don't double count edges
        return self->m / 2;
    }
}

bool graph_directed(graph* self) {
    return self->directed;
}

// Private helper function for location a neighboring vertex
// in the adjacency list of another vertex.
int graph_edge_search(graph* self, vertex_t u, vertex_t v) {
    assert(u < self->n && v < self->n);

    int loc = -1;
    for (size_t i = 0; i < self->degree[u]; i++) {
        if (self->adj_list[u][i] == v) {
          loc = i;
        }
    }
    return loc;
}

graph* graph_edge(graph* self, vertex_t u, vertex_t v, bool* has_edge) {
    if (u >= self->n || v >= self->n) { return NULL; }

    *has_edge = false;
    if (graph_edge_search(self, u, v) >= 0) {
      *has_edge = true;
    }

    return self;
}

graph* graph_degree(graph* self, vertex_t u, size_t* deg) {
    if (u >= self->n) { return NULL; }

    *deg = self->degree[u];

    return self;
}

graph* graph_neighbors(graph* self, vertex_t u, vertex_t* vs) {
    if (u >= self->n) { return NULL; }

    for (size_t i = 0; i < self->degree[u]; i++) vs[i] = self->adj_list[u][i];

    return self;
}

graph* graph_add_edge(graph* self, vertex_t u, vertex_t v) {
    if (u >= self->n || v >= self->n) { return NULL; }

    bool has_edge = false;
    graph_edge(self, u, v, &has_edge);
    if (!has_edge) { // Do nothing if edge already exists
        self->adj_list[u][self->degree[u]] = v;
        self->degree[u]++;
        self->m++;
        if (!self->directed) { // Add reverse edge if graph is undirected
            self->adj_list[v][self->degree[v]] = u;
            self->degree[v]++;
            self->m++;
        }
    }

    return self;
}

graph* graph_remove_edge(graph* self, vertex_t u, vertex_t v) {
    if (u >= self->n || v >= self->n) { return NULL; }

    int loc = graph_edge_search(self, u, v);
    if (loc >= 0) {
        self->adj_list[u][loc] = self->adj_list[u][self->degree[u] - 1];
        self->degree[u]--;
        self->m--;
        if (!self->directed) {
            loc = graph_edge_search(self, v, u);
            assert(loc >= 0);
            self->adj_list[v][loc] = self->adj_list[v][self->degree[v] - 1];
            self->degree[v]--;
            self->m--;
        }
    }

    return self;
}

// Note: The following method was used for testing, but is not part of the API.
void graph_write(graph* self, FILE* stream)
{
    fprintf(stream, "n = %zu\n", self->n);
    fprintf(stream, "m = %zu\n", self->m);
    fprintf(stream, "directed = %s\n\n", self->directed ? "true" : "false");

    for (size_t i = 0; i < self->n; i++) {
        fprintf(stream, "%zu : ", i);
        for (size_t j = 0; j < self->degree[i]; j++) {
            fprintf(stream, "%zu ", self->adj_list[i][j]);
        }
        fprintf(stream, "[%zu]\n", self->degree[i]);
    }
}
