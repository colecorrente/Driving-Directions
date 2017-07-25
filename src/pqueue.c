#include "pqueue.h"

// For pqueue_print
#include <stdio.h>

// Get parent index
size_t parent(size_t child)
{
    assert(child > 0);
    return (child - 1) / 2;
}

// Get left child index
size_t left_child(size_t parent)
{
    assert(parent < PQUEUE_SIZE);
    return 2*parent + 1;
}

// Get right child index
size_t right_child(size_t parent)
{
    assert(parent < PQUEUE_SIZE);
    return 2*parent + 2;
}


void pqueue_init(pqueue *self)
{
    self->size = 0;
}


// Private helper that allows percolation from any index in the heap
void percolate_up_from(pqueue *self, size_t pos)
{
    bool found = false;
    while ((pos > 0) && !found) // While not at the root
    {
        if (self->heap[parent(pos)].priority > self->heap[pos].priority)
        {
            pqueue_item tmp = self->heap[parent(pos)];
            self->heap[parent(pos)] = self->heap[pos];
            self->heap[pos] = tmp;
            pos = parent(pos);
        }
        else // Found the correct location!
        {
            found = true;
        }
    }
}


void percolate_up(pqueue *self) {
  percolate_up_from(self, self->size-1);
}


pqueue* pqueue_push(pqueue *self, vertex_t key, double priority)
{
    if (self->size == PQUEUE_SIZE) return NULL;
    self->heap[self->size].key = key;
    self->heap[self->size].priority = priority;
    self->size++;
    percolate_up(self);
    return self;
}


void percolate_down(pqueue *self)
{
    size_t pos = 0;
    bool found = false;
    while (left_child(pos) < self->size && !found) // While pos has a child
    {
        // Find smallest child
        size_t child = left_child(pos);
        if ((child + 1 < self->size) &&
                (self->heap[child+1].priority < self->heap[child].priority))
        {
            child++;
        }

        // Swap if smallest child is smaller than parent
        if (self->heap[pos].priority > self->heap[child].priority)
        {
            pqueue_item tmp = self->heap[child];
            self->heap[child] = self->heap[pos];
            self->heap[pos] = tmp;
            pos = child;
        }
        else // Found the correct location!
        {
            found = true;
        }
    }
}


pqueue* pqueue_pop(pqueue *self)
{
    if (pqueue_empty(self)) return NULL;
    self->heap[0] = self->heap[self->size - 1];
    self->size--;
    percolate_down(self);
    return self;
}


pqueue* pqueue_top(pqueue *self, vertex_t *key, double *priority)
{
    if (pqueue_empty(self)) return NULL;
    if (key != NULL) *key = self->heap[0].key;
    if (priority != NULL) *priority = self->heap[0].priority;
    return self;
}


size_t pqueue_size(pqueue *self)
{
    return self->size;
}


bool pqueue_empty(pqueue *self)
{
    return pqueue_size(self) == 0;
}

pqueue* pqueue_adjust_priority(pqueue *self, vertex_t key, double new_priority)
{
    size_t i;
    for (i = 0; i < self->size; ++i) {
        if (self->heap[i].key == key) {
            self->heap[i].priority = new_priority;
            break;
        }
    }
    if (i >= self->size) {
      return NULL;
    }
    percolate_up_from(self, i);
    return self;
    
}

void pqueue_print(pqueue *self)
{
    printf("PQueue of size %zu:\n", self->size);
    for (size_t i = 0; i < self->size; ++i) {
        printf(" %lu [%.3f]", self->heap[i].key, self->heap[i].priority);
    }
    printf("\n");
}
