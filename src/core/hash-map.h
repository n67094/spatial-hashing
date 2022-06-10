#ifndef CORE_HASH_MAP_H
#define CORE_HASH_MAP_H

#include <assert.h>

#ifdef NDEBUG
  #define HASH_MAP_CHECKS(hash_map)                                            \
    {                                                                          \
      assert(hash_map != NULL);                                                \
      assert(hash_map->array != NULL);                                         \
      assert(hash_map->hash != NULL);                                          \
    }
#else
  #define HASH_MAP_CHECKS(hash_map)
#endif

typedef int (*HashingCallback)(int key);

typedef struct HashMapItem {
  int key;
  void *value;
} HashMapItem;

typedef struct HashMap {
  HashingCallback hash;
  HashMapItem *array;
  int size;
  int max_size;
  size_t size_type;
} HashMap;

/*
 * Create an hash map
 * keys are initialized with -1
 * values is the result of a malloc with size_type size
 */
HashMap *
HashMapCreate(int size, size_t size_type, HashingCallback hashing_callback);

void HashMapInsert(HashMap *hash_map, int key, void *value);

HashMapItem *HashMapSearch(HashMap *hash_map, int key);

/*
 * Delete an element
 * Key is reset to -1
 * value is the result of realloc with size_type size
 */
void HashMapErase(HashMap *hash_map, int key);

/*
 * return the siz, total of elements used
 */
int HashMapSize(HashMap *hash_map);

/*
 * return the max size, total elements used and unused
 */
int HashMapMaxSize(HashMap *hash_map);

/*
 * Clear an hash map
 * keys are reset to -1
 * values are reallocated
 */
void HashMapClear(HashMap *Hash_map);

/*
 * Free all allocated element
 * @hash_map is passed by reference so it can be set to null for parent caller
 */
void HashMapDestroy(HashMap **hash_map);

#endif
