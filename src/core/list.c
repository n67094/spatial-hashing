#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "log.h"

// TODO invert head and tail ? tail should be start at head should be end at

static ListItem *ListCopyValue(List *list, void *value)
{
  assert(list != NULL);
  assert(value != NULL);

  ListItem *item = malloc(sizeof(ListItem));
  if (item == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  item->next = NULL;
  item->previous = NULL;

  item->value = malloc(list->size_type);
  if (item->value == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  memcpy(item->value, value, list->size_type);

  return item;
}

List *ListCreate(size_t size_type)
{
  assert(size_type > 0);

  List *list = malloc(sizeof(List));

  if (list == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  list->size = 0;
  list->tail = NULL;
  list->head = NULL;
  list->size_type = size_type;

  return list;
}

void ListUnshift(List *list, void *value)
{
  assert(list != NULL);
  assert(value != NULL);

  ListItem *item = ListCopyValue(list, value);
  if(item == NULL)
    return;

  if (list->size > 0) {
    item->next = list->tail;
    list->tail->previous = item;
  } else {
    list->head = item;
  }

  list->tail = item;
  list->size += 1;

  return;
}

int ListShift(List *list)
{
  assert(list != NULL);

  if (list->size > 0) {
    ListItem *toRemove = list->tail;

    list->tail = toRemove->next;
    list->tail->previous = NULL;

    list->size -= 1;

    free(toRemove);
    toRemove = NULL;

    return 1;
  }

  return 0;
}

void ListPush(List *list, void *value)
{
  assert(list != NULL);
  assert(value != NULL);

  ListItem *item = ListCopyValue(list, value);
  if (item == NULL)
    return;

  if (list->size > 0) {
    item->previous = list->head;
    list->head->next = item;
  } else {
    list->tail = item;
  }

  list->head = item;
  list->size += 1;
}

int ListPop(List *list)
{
  assert(list != NULL);

  if (list->size > 0) {
    ListItem *toRemove = list->head;

    list->head = toRemove->previous;
    list->head->next = NULL;

    list->size -= 1;

    free(toRemove);
    toRemove = NULL;

    return 1;
  }

  return 0;
}

void ListPushAll(List *list_a, List *list_b)
{
  assert(list_a != NULL);
  assert(list_b != NULL);

  ListItem *pointer;
  for (pointer = list_b->tail; pointer != NULL; pointer = pointer->next) {
    ListPush(list_a, pointer->value);
  }
}

int ListSize(List *list)
{
  assert(list != NULL);

  return list->size;
}

bool ListContains(List *list, void *value, CallbackCompare callback_compare)
{
  assert(list != NULL);
  assert(value != NULL);

  // nothing to compare
  if (list->size == 0)
    return false;

  ListItem *pointer;
  for (pointer = list->tail; pointer != NULL; pointer = pointer->next) {
    if (callback_compare(pointer->value, value) == 0)
      return true;
  }

  return false;
}

int ListDestroy(List **list)
{
  assert(*list != NULL);

  ListItem *pointer = (*list)->tail;

  int i = 0;
  while (i < (*list)->size) {
    if (pointer->value != NULL) { // free item value
      free(pointer->value);
      pointer->value = NULL;
    }

    ListItem *tmp = pointer;
    pointer = pointer->next;

    if (tmp != NULL) {
      free(tmp); // free item
      tmp = NULL;
    }

    ++i;
  }

  free(*list);
  *list = NULL;
  return i;
}
