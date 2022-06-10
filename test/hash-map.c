#include <stdio.h>

#include "hash-map.h"

#include "../src/core/hash-map.h"
#include "minunit.h"

#define TEST_HASH_MAP_SIZE 5

static int Hash(int key) { return key % 20; }

void TestPrintHashMap(HashMap *hash_map)
{
  if(hash_map != NULL) {
    printf("==========\n");
    printf("size: %d\n", hash_map->size);
    printf("max_size: %d\n", hash_map->max_size);

    HashMapItem* array = hash_map->array;

    for (int i = 0; i < hash_map->size; ++i) {
      if(array[i].value != NULL) {
        printf("key : %d value: %d\n", array[i].key, *(int *)array[i].value);
      } else {
        printf("key : %d value: %s\n", array[i].key, "NULL");
      }
    }
    printf("==========\n");
  }
}

 char *TestHashMapInsert(void)
{
  int one = 1;
  int two = 2;
  int tree = 3;

  HashMap *hash_map = HashMapCreate(TEST_HASH_MAP_SIZE, sizeof(int), Hash);

  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 4, &tree);

  printf("hash map size %d\n", hash_map->size);

  TestPrintHashMap(hash_map);

  mu_assert("Error, size should be 3", hash_map->size == 3);
  mu_assert("Error, max_size should be 5",
            hash_map->max_size == TEST_HASH_MAP_SIZE);

  HashMapDestroy(&hash_map);

  return 0;
}

char *TestHashMapErase(void)
{
  int one = 1;
  int two = 2;
  int tree = 3;

  HashMap *hash_map = HashMapCreate(TEST_HASH_MAP_SIZE, sizeof(int), Hash);

  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 4, &tree);

  HashMapErase(hash_map, 1);
  HashMapErase(hash_map, 4);

  mu_assert("Error, size should be 1", hash_map->size == 1);
  mu_assert("Error, max_size should be 5",
            hash_map->max_size == TEST_HASH_MAP_SIZE);

  HashMapDestroy(&hash_map);

  return 0;
}

char *TestHashMapSearch(void)
{
  int one = 1;
  int two = 2;
  int tree = 3;

  HashMap *hash_map = HashMapCreate(TEST_HASH_MAP_SIZE, sizeof(int), Hash);

  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 4, &tree);

  HashMapItem *search1 = HashMapSearch(hash_map, 1);
  mu_assert("Error, search1 key should be 1", search1->key == 1);
  mu_assert("Error, search1 value should be 1", *(int *)search1->value == 1);

  HashMapItem *search2 = HashMapSearch(hash_map, 4);
  mu_assert("Error, search2 key should be 4", search2->key == 4);
  mu_assert("Error, search2 value should be 3", *(int *)search2->value == 3);

  HashMapDestroy(&hash_map);

  return 0;
}

char *TestHashMapDestroy(void)
{
  int one = 1;
  int two = 2;
  int tree = 3;

  HashMap *hash_map = HashMapCreate(TEST_HASH_MAP_SIZE, sizeof(int), Hash);

  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 1, &one);
  HashMapInsert(hash_map, 4, &tree);

  HashMapDestroy(&hash_map);

  mu_assert("Error, should destroy", hash_map == NULL);

  return 0;
}
