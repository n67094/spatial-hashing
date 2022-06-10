#ifndef CORE_LIST_H
#define CORE_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef int(*CallbackCompare)(void *a, void *b);

typedef struct ListItem {
  void *value;
  struct ListItem *previous;
  struct ListItem *next;
} ListItem;

typedef struct List {
  ListItem *head;
  ListItem *tail;
  int size;
  size_t size_type;
} List;

List *ListCreate(size_t size_type);

void ListUnshift(List *list, void *value);

int ListShift(List *list);

void ListPush(List *list, void *value);

int ListPop(List *list);

void ListPushAll(List *listA, List *listB);

int ListSize(List *list);

bool ListContains(List *list, void *value, CallbackCompare callback_compare);

// return :
// -1 if list == NULL
// 0 if no item to free
// the number of item free
// pass the pointer by reference and not value to change it to NULL
int ListDestroy(List **list);

#endif
