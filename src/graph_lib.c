#include "graph_lib.h"
#include "pqueue.h"
#include "queue.h"

graph* graph_edge_reversal(graph* G) {
    size_t vertexCount = graph_vertex_count(G);
    graph* newG = graph_create(vertexCount, graph_directed(G));

    vertex_t neighbors[vertexCount];
    size_t deg = 0;

    for (vertex_t i = 0; i < vertexCount; i++){
        deg = 0;
        if (graph_degree(G, i, &deg) != NULL && graph_neighbors(G, i, neighbors) != NULL){
            for (vertex_t j = 0; j < deg; j++){
                graph_add_edge(newG, neighbors[j], i);
            }
        }
    }
    return newG;
}

void graph_bfs(graph* G, vertex_t start, vertex_t* parent) {
    size_t i;

    size_t n = graph_vertex_count(G);

    bool marked[n];
    for (i = 0; i < n; ++i) {
        parent[i] = i;
        marked[i] = false;
    }

    marked[start] = true;
    queue* Q = queue_create();
    queue_add_last(Q, start);

    while (!queue_empty(Q)) {
        // vertex_t current = first elt in Q
        vertex_t current;
        queue_get_first(Q, &current);
        queue_remove_first(Q);

        // vertex_t neighbors[n] = neighbors of current
        size_t current_deg;
        graph_degree(G, current, &current_deg);
        vertex_t neighbors[n];
        graph_neighbors(G, current, neighbors);

        for (i = 0; i < current_deg; ++i) {
            if (!marked[neighbors[i]]) {
                marked[neighbors[i]] = true;
                parent[neighbors[i]] = current;
                queue_add_last(Q, neighbors[i]);
            }
        }
    }
    queue_destroy(Q);
}

//private method
void graph_bfs_marked(graph* G, vertex_t start, bool* marked) {
    size_t i;

    size_t n = graph_vertex_count(G);

    vertex_t parent[n];
    for (i = 0; i < n; ++i) {
        parent[i] = i;
        marked[i] = false;
    }

    marked[start] = true;
    queue* Q = queue_create();
    queue_add_last(Q, start);

    while (!queue_empty(Q)) {
        // vertex_t current = first elt in Q
        vertex_t current;
        queue_get_first(Q, &current);
        queue_remove_first(Q);

        // vertex_t neighbors[n] = neighbors of current
        size_t current_deg;
        graph_degree(G, current, &current_deg);
        vertex_t neighbors[n];
        graph_neighbors(G, current, neighbors);

        for (i = 0; i < current_deg; ++i) {
            if (!marked[neighbors[i]]) {
                marked[neighbors[i]] = true;
                parent[neighbors[i]] = current;
                queue_add_last(Q, neighbors[i]);
            }
        }
    }
    queue_destroy(Q);
}

bool graph_is_connected(graph* G){
    size_t n = graph_vertex_count(G);
    bool marked[n];
    bool markedrev[n];

    graph_bfs_marked(G,0,marked);
    graph* revg = graph_edge_reversal(G);
    graph_bfs_marked(revg,0,markedrev);
    graph_destroy(revg);

    for (size_t i = 0; i < n; i++){
        if (marked[i] == false || markedrev[i] == false) {
            return false;
        }
    }
    return true;
}

void graph_dijkstras(graph* G, vertex_t start, vertex_t* parent, double** edge_length){
    size_t i;
    size_t n = graph_vertex_count(G);
    double distance[n];
    bool marked[n];
    bool in_pq = false;

    for (i = 0; i < n; ++i) {
        parent[i] = start;
        marked[i] = false;
        distance[i] = 10000000000000.0;
    }

    distance[start] = 0.0;
    marked[start] = true;

    pqueue* pq = malloc(sizeof(pqueue));
    pqueue_init(pq);
    pqueue_push(pq, start, distance[start]);

    while (!pqueue_empty(pq)) {
        // vertex_t current = first elt in Q
        vertex_t current;
        double current_priority;
        pqueue_top(pq, &current, &current_priority);
        pqueue_pop(pq);

        // vertex_t neighbors[n] = neighbors of current
        size_t current_deg;
        graph_degree(G, current, &current_deg);
        vertex_t neighbors[n];
        graph_neighbors(G, current, neighbors);

        for (i = 0; i < current_deg; ++i) {
            if (!marked[neighbors[i]]) {
                marked[neighbors[i]] = true;

                double addition = edge_length[current][neighbors[i]] > 0.0 ? edge_length[current][neighbors[i]] : 0.0;
                double new_dist = distance[current] + addition;
                if (new_dist < distance[neighbors[i]]){
                    distance[neighbors[i]] = new_dist;
                    parent[neighbors[i]] = current;

                    in_pq = false;
                    for (size_t i = 0; i < pqueue_size(pq); i++){
                        if (pq->heap[i].key == neighbors[i]) {
                            in_pq = true;
                        }
                    }
                    if (in_pq){
                        pqueue_adjust_priority(pq,neighbors[i], new_dist);
                    } else{
                        pqueue_push(pq, neighbors[i], new_dist);
                    }
                }
            }
        }
    }
    free(pq);
}

void graph_traverse_parents(vertex_t* parent, vertex_t start, vertex_t end, vertex_t* path, int* path_size){
    int count = 2;
    vertex_t current = parent[end];
    while (current != start){
        current = parent[current];
        count++;
    }

    *path_size = count;
    vertex_t revpath[count];

    revpath[0] = end;
    count = 1;
    current = parent[end];
    while (current != start){
        revpath[count] = current;
        current = parent[current];
        count++;
    }
    revpath[count] = start;

    for (int i = count; i >= 0; i--){
        path[count-i] = revpath[i];
    }
}
