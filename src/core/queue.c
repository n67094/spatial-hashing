#include <stdbool.h>
#include <stdlib.h>

#include "log.h"
#include "queue.h"

Queue *QueueCreate(int max_size, size_t size_type)
{
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  queue->back = -1;
  queue->front = 0;
  queue->size = 0;
  queue->max_size = max_size;
  queue->size_type = size_type;
  queue->array = calloc(max_size, size_type);

  return queue;
}

void *QueueFront(Queue *queue)
{
  return (queue->array + (queue->front * queue->size_type));
}

void *QueueBack(Queue *queue)
{
  return (queue->array + (queue->back * queue->size_type));
}

void QueuePush(Queue *queue, void *value) {
  if (QueueIsFull(queue))
    return; // overflow

  // if the size is at max is set to -1 to go at index 0 next line
  if (queue->back == queue->max_size)
    queue->back = -1;

  ++queue->back;

  void *array = queue->array;
  int offset = queue->back * queue->size_type;

  int i;
  for (i = 0; i < queue->size_type; ++i)
    *(char *)(array + offset + i) = *(char *)(value + i);

  ++queue->size;
}

void QueuePop(Queue *queue)
{
  if (QueueIsEmpty(queue))
    return; // underflow

  ++queue->front;

  if(queue->front == queue->max_size)
    queue->front = 0;

  --queue->size;
}

bool QueueIsEmpty(Queue *queue) { return queue->size == 0; }

bool QueueIsFull(Queue *queue) { return queue->size == queue->max_size; }

int QueueSize(Queue *queue) { return queue->size; }

void QueueDestroy(Queue **queue) {
  if (queue == NULL)
    return;

  if((*queue)->array != NULL) {
    free((*queue)->array);
    (*queue)->array = NULL;
  }

  free(*queue);
  *queue = NULL;
}
