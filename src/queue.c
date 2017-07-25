#include "queue.h"

typedef struct queue_node queue_node;

struct queue {
    size_t count;
    queue_node* head;
    queue_node* tail;
};

// Internal nodes used by queue
struct queue_node {
    vertex_t data;
    queue_node* next;
    queue_node* prev;
};

// Private helper method for creating a queue_node
queue_node* queue_node_create(
  vertex_t data,
  queue_node* prev,
  queue_node* next
) {
    // Allocate
    queue_node* node = malloc(sizeof(queue_node));
    if (node == NULL) { return NULL; }
    // Initialize
    node->data = data;
    node->prev = prev;
    node->next = next;
    // Return
    return node;
}

queue* queue_create() {
    // Allocate
    queue* new_list = malloc(sizeof(queue));
    if (new_list == NULL) { return NULL; }
    // Initialize
    new_list->count = 0;
    new_list->head = NULL;
    new_list->tail = NULL;
    // Return
    return new_list;
}

void queue_destroy(queue* self) {
    // Free all nodes
    queue_node* finger = self->head;
    while (finger != NULL) {
        queue_node* temp = finger;
        finger = finger->next;
        free(temp);
    }
    // Free the queue
    free(self);
}

queue* queue_get_first(queue* self, vertex_t* value) {
    if (self->head == NULL) { return NULL; }
    *value = self->head->data;
    return self;
}

queue* queue_add_last(queue* self, vertex_t value) {
    queue_node* node = queue_node_create(value, self->tail, NULL);
    if (node == NULL) { return NULL; }

    if (self->head == NULL) { self->head = node; }
    if (self->tail != NULL) { self->tail->next = node; }
    self->tail = node;
    self->count++;
    return self;
}

queue* queue_remove_first(queue* self) {
    if (self->head == NULL) { return NULL; }
    queue_node* temp = self->head;
    self->head = self->head->next;
    if (self->head == NULL) {
        self->tail = NULL;
    } else {
        self->head->prev = NULL;
    }
    self->count--;
    free(temp);
    return self;
}

size_t queue_size(queue* self) {
    return self->count;
}

bool queue_empty(queue* self) {
    return self->count == 0;
}
