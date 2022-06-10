#include <stdio.h>

#include "list.h"

#include "../src/core/list.h"
#include "minunit.h"

char *TestListPush(void)
{
  List *list = ListCreate(sizeof(int));

  int one = 1;
  int two = 2;

  ListPush(list, &one);
  ListPush(list, &two);

  mu_assert("Error, size should be 2", ListSize(list) == 2);

  ListDestroy(&list);

  return 0;
}

char *TestListPop(void)
{
  List *list = ListCreate(sizeof(int));

  int one = 1;
  int two = 2;

  ListPush(list, &one);
  ListPush(list, &two);

  mu_assert("Error, size should be 2", ListSize(list) == 2);

  int isSuccess = ListPop(list);

  mu_assert("Error, size should be 2", ListSize(list) == 1);
  mu_assert("Error, pop should succeed", isSuccess == 1);

  ListDestroy(&list);

  return 0;
}

char *TestListUnshift(void)
{
  List *list = ListCreate(sizeof(int));

  int one = 1;
  int two = 2;

  ListUnshift(list, &one);
  ListUnshift(list, &two);

  mu_assert("Error, size should be 2", ListSize(list) == 2);

  ListDestroy(&list);

  return 0;
}

char *TestListShift(void)
{
  List *list = ListCreate(sizeof(int));

  int one = 1;
  int two = 2;

  ListUnshift(list, &one);
  ListUnshift(list, &two);

  mu_assert("Error, size should be 2", ListSize(list) == 2);

  int isSuccess = ListShift(list);

  mu_assert("Error, size should be 1", ListSize(list) == 1);
  mu_assert("Error, shift should succeed", isSuccess == 1);

  ListDestroy(&list);

  return 0;
}

char* TestListDestroy(void)
{
  List *list = ListCreate(sizeof(int));

  int one = 1;
  int two = 2;

  ListUnshift(list, &one);
  ListUnshift(list, &two);

  int count = ListDestroy(&list);

  mu_assert("Error, should destroy and delete count 2 items", count == 2);

  return 0;
}
