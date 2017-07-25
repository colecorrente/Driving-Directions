/**
 * This file provides a queue based on a double linked list. This is the same
 * queue we used in lab.
 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

/**
 * Forward declared queue struct, hiding implementation details.
 */
typedef unsigned long vertex_t;
typedef struct queue queue;


/**
 * Creates a heap allocated queue.
 *
 * Time: O(1)
 *
 * @return a pointer to a new queue or NULL if an memory allocation failed.
 * @post a queue is allocated
 */
queue* queue_create();

/**
 * Frees all memory associated with a queue.
 *
 * Time: O(n)
 *
 * @param self a queue to be destroyed
 * @post all memory used by the queue is deallocated
 */
void queue_destroy(queue* self);

/**
 * Gets the value of the first element in the queue.
 *
 * Time: O(1)
 *
 * @param self the queue
 * @param value[out] where the value is returned
 * @pre the queue is not empty
 * @return self or NULL if preconditions are not met
 */
queue* queue_get_first(queue* self, vertex_t* value);

/**
 * Adds an element to the back of the list.
 *
 * Time: O(n)
 * Note: This is O(1) for a double queue.
 *
 * @param self the queue
 * @param value the value being added
 * @return self or NULL if memory allocation failed
 * @post value is added to the end of the list
 */
queue* queue_add_last(queue* self, vertex_t value);

/**
 * Removes the first element.
 *
 * Time: O(1)
 *
 * @param self the queue
 * @pre the list is not empty
 * @return self or NULL if preconditions are not met
 * @post the first element is removed
 */
queue* queue_remove_first(queue* self);

/**
 * Gets the size of the queue.
 *
 * Time: O(1)
 *
 * @param self the queue
 * @return the number of items in the queue
 */
size_t queue_size(queue* self);

/**
 * TODO
 * @param  self [description]
 * @return      [description]
 */
bool queue_empty(queue* self);

#endif//__queue_H__
