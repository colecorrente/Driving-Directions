/**
 * @file pqueue.h
 *
 * A header file for a simple priority queue, containing vertex_t keys and double
 * priorities. The function prototypes in this header file define the API for
 * working with pqueue.
 *
 * Warning: This data structure was created before we knew about malloc, and
 * therefore does some things in different ways. In particular, you will be
 * working directly with pqueue not a pointer.
 *
 * @author Michael J. Bannister
 * @date 03 Dec 2015
 */
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

#define PQUEUE_SIZE 1000
typedef unsigned long vertex_t;

/*
 * Struct for holding an association of a key and a priority.
 */
typedef struct pqueue_item
{
    vertex_t key;
    double priority;
} pqueue_item;

/**
 * Struct that is the actual priority queue "object".
 */
typedef struct pqueue
{
    size_t size;
    pqueue_item heap[PQUEUE_SIZE];
} pqueue;


/**
 * @brief Initializes a new empty pqueue.
 *
 * @param self a pointer to the pqueue
 */
void pqueue_init(pqueue *self);


/**
 * @brief Adds an item to the pqueue with the given key and priority.
 *
 * @param self a pointer to the pqueue
 * @param key the key to add
 * @param priority the priority of the key
 * @pre the current size of pqueue is less than PQUEUE_SIZE
 * @return self if preconditions are met and NULL otherwise
 * @post the item (key, priority) is added to pqueue
 */
pqueue* pqueue_push(pqueue *self, vertex_t key, double priority);


/**
 * @brief Removes the item with lowest priority.
 *
 * @param self a pointer to the pqueue
 * @pre the current size of pqueue is non-empty
 * @return self if preconditions are met and NULL otherwise
 * @post the item with lowest priority is removed from pqueue
 */
pqueue* pqueue_pop(pqueue *self);


/**
 * @brief Returns the key and priority of the item with lowest priority.
 *
 * Note: output parameters may be NULL if the caller does not need this output.
 *
 * @param self a pointer to the pqueue
 * @param[out] key a pointer to return the key to
 * @param[out] priority a pointer to return the priority to
 * @pre the current size of pqueue is non-empty
 * @return self if preconditions are met and NULL otherwise
 */
pqueue* pqueue_top(pqueue *self, vertex_t *key, double *priority);


/**
 * @brief Returns the number of items in the pqueue.
 *
 * @param self a pointer to the pqueue
 * @return the number of items in pqueue
 */
size_t pqueue_size(pqueue *self);


/**
 * @brief Returns the emptiness of pqueue.
 *
 * @param self a pointer to the pqueue
 * @return true if the pqueue is empty and false otherwise
 */
bool pqueue_empty(pqueue *self);

/**
 *
 * @brief Adjusts the priority of an item in the queue.
 *
 * Note: this searches the queue for the item, so it's O(n)
 * If the given vertex doesn't exist in the heap, this function returns NULL
 * instead of the adjusted queue.
 *
 * @param self a pointer to the pqueue being adjusted
 * @param key the vertex for which we want to adjust priority
 * @param new_priority the new priority of that vertex
 *
 * @return the pqueue that's been adjusted
 *
 */
pqueue* pqueue_adjust_priority(pqueue *self, vertex_t key, double new_priority);

/**
 * @brief Prints out a priority queue to stdout.
 *
 * #param welf a pointer to the queue to print
 */
void pqueue_print(pqueue *self);

#endif//__PQUEUE_H__
