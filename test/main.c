#include <stdio.h>

#include "hash-map.h"
#include "list.h"
#include "minunit.h"
#include "queue.h"

int tests_run;

static char *AllTests()
{
  printf("HASHMAP TESTS\n");
  printf("=====================================================\n");

  mu_run_test(TestHashMapInsert);
  mu_run_test(TestHashMapErase);
  mu_run_test(TestHashMapSearch);
  mu_run_test(TestHashMapDestroy);

  printf("LIST TESTS\n");
  printf("=====================================================\n");

  mu_run_test(TestListPush);
  mu_run_test(TestListPop);
  mu_run_test(TestListUnshift);
  mu_run_test(TestListShift);
  mu_run_test(TestListDestroy);

  printf("QUEUE TESTS\n");
  printf("=====================================================\n");

  mu_run_test(TestQueuePush);
  mu_run_test(TestQueuePop);
  mu_run_test(TestQueueIsEmpty);
  mu_run_test(TestQueueIsFull);
  mu_run_test(TestQueueDestroy);

  return 0;
}

int main(int argc, char *argv[])
{
  char *result = AllTests();

  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }

  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
