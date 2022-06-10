#include "queue.h"

#include "../src/core/queue.h"
#include "minunit.h"

char *TestQueuePush(void) {
  int one = 1;
  int two = 2;

  Queue *queue = QueueCreate(5, sizeof(int));

  QueuePush(queue, &one);
  QueuePush(queue, &two);

  mu_assert("Error, size should be 2", QueueSize(queue) == 2);
  mu_assert("Error, should not be empty", QueueIsEmpty(queue) == false);
  mu_assert("Error, should not be full", QueueIsFull(queue) == false);
  mu_assert("Error, front should 1", *(int*)QueueFront(queue) == 1);
  mu_assert("Error, back should 1", *(int *)QueueBack(queue) == 2);

  return 0;
}

char *TestQueuePop(void) {
  int one = 1;
  int two = 2;
  int tree = 3;

  Queue *queue = QueueCreate(5, sizeof(int));

  QueuePush(queue, &one);
  QueuePush(queue, &two);
  QueuePush(queue, &tree);


  mu_assert("Error, size should be 3", QueueSize(queue) == 3);
  mu_assert("Error, should not be empty", QueueIsEmpty(queue) == false);
  mu_assert("Error, should not be full", QueueIsFull(queue) == false);
  mu_assert("Error, front should 1", *(int*)QueueFront(queue) == 1);
  mu_assert("Error, back should 3", *(int *)QueueBack(queue) == 3);

  QueuePop(queue);

  mu_assert("Error, size should be 2", QueueSize(queue) == 2);
  mu_assert("Error, front should 2", *(int*)QueueFront(queue) == 2);
  mu_assert("Error, back should 3", *(int *)QueueBack(queue) == 3);

  return 0;
}

char* TestQueueIsEmpty(void) {
  Queue *queue = QueueCreate(5, sizeof(int));

  mu_assert("Error, should not be empty", QueueIsEmpty(queue) == true);
  mu_assert("Error, should not be full", QueueIsFull(queue) == false);

  return 0;
}

char* TestQueueIsFull(void) {
  int one = 1;
  int two = 2;
  int tree = 3;

  Queue *queue = QueueCreate(3, sizeof(int));

  QueuePush(queue, &one);
  QueuePush(queue, &two);
  QueuePush(queue, &tree);

  mu_assert("Error, should not be empty", QueueIsEmpty(queue) == false);
  mu_assert("Error, should not be full", QueueIsFull(queue) == true);

  return 0;
}

char *TestQueueDestroy(void) {
  int one = 1;
  int two = 2;
  int tree = 3;

  Queue *queue = QueueCreate(5, sizeof(int));

  QueuePush(queue, &one);
  QueuePush(queue, &two);
  QueuePush(queue, &tree);

  QueueDestroy(&queue);

  mu_assert("Error, should destroy", queue == NULL);

  return 0;
}
