#ifndef CORE_QUEUE
#define CORE_QUEUE

#include <stdbool.h>
#include <stdlib.h>

typedef struct Queue {
  int back;
  int front;
  int size;
  int max_size;
  size_t size_type;
  void *array;
} Queue;

// Create a queue of @size
Queue *QueueCreate(int max_size, size_t size_type);

// get the element at the front
void *QueueFront(Queue* queue);

// get the element at the back
void *QueueBack(Queue* queue);

// insert element at the back
void QueuePush(Queue *queue, void *value);

// remove the element at the front
void QueuePop(Queue *queue);

// return true if empty
bool QueueIsEmpty(Queue *queue);

// returne true if full
bool QueueIsFull(Queue *queue);

// return the number of element
int QueueSize(Queue *queue);

// Free the queue and it's elements
void QueueDestroy();

#endif
