#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash-map.h"
#include "log.h"

HashMap *HashMapCreate(int max_size, size_t size_type, HashingCallback hash)
{
  assert(max_size > 0);

  HashMapItem *array = malloc(sizeof(HashMapItem) * max_size);
  if (array == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  int i;
  for (i = 0; i < max_size; ++i) {
    array[i].key = i;
    array[i].value = malloc(size_type);

    if (array[i].value == NULL) {
      LOG_ERROR("allocation");
      return NULL;
    }
  }

  HashMap *hash_map = malloc(sizeof(HashMap));
  if (hash_map == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  hash_map->hash = hash;
  hash_map->array = array;
  hash_map->max_size = max_size;
  hash_map->size_type = size_type;
  hash_map->size = 0;

  return hash_map;
}

void HashMapInsert(HashMap *hash_map, int key, void *value)
{
  HASH_MAP_CHECKS(hash_map);

  if (hash_map->size + 1 > hash_map->max_size) { // no more space available
    return;
  }

  int index = hash_map->hash(key);
  index = index % hash_map->max_size;

  HashMapItem *array = hash_map->array;
  /*
    while (array[index].key != -1) {
      ++index;
      index %= hash_map->max_size;
    }
  */
  array[index].key = key;
  array[index].value = value;

  /*
  int i;
  for (i = 0; i < hash_map->size_type; i++)
    *(char *)(array[index].value + i) = *(char *)(value + i);
  */

  hash_map->size++;
}

HashMapItem *HashMapSearch(HashMap *hash_map, int key)
{
  HASH_MAP_CHECKS(hash_map);

  int index = hash_map->hash(key);

  HashMapItem *array = hash_map->array;

  // to take care of the wraparound if each hash is the same for all elements
  int count_wraparound = 0;

  // if the hash is the same for more than one element they are append one after
  // the other so here we take care of packed hash
  while (/*(array + index)->key != -1 &&*/ count_wraparound <= hash_map->max_size) {
    if ((array + index)->key == key) {
      return (array + index);
    }

    ++index;
    ++count_wraparound;
    index %= hash_map->max_size;
  }

  return NULL;
}

void HashMapErase(HashMap *hash_map, int key)
{
  HASH_MAP_CHECKS(hash_map);

  if (hash_map->size == 0) {
    LOG_INFO("nothing to delete");
    return;
  }

  int index = hash_map->hash(key);
  index = index % hash_map->max_size;

  HashMapItem *array = hash_map->array;

  // to take care of the wraparound if each hash is the same for all elements
  int count_wraparound = 0;

  while (/*array[index].key != -1 &&*/ count_wraparound < hash_map->max_size) {

    if (array[index].key == key) {
      array[index].key = -1;

      if(array[index].value != NULL) {
        array[index].value = realloc(array[index].value, hash_map->size_type);
      }

      hash_map->size--;
      return;
    }

    ++index;
    ++count_wraparound;

    index %= hash_map->max_size;
  }
}

int HashMapSize(HashMap *hash_map)
{
  HASH_MAP_CHECKS(hash_map);
  return hash_map->size;
}

int HashMapMaxSize(HashMap *hash_map)
{
  HASH_MAP_CHECKS(hash_map);
  return hash_map->max_size;
}

void HashMapClear(HashMap *hash_map)
{
  HashMapItem *array = hash_map->array;

  int i;
  for (i = 0; i < hash_map->max_size; ++i) {
    array[i].key = -1;
    array[i].value = NULL;
    //    if(array[i].value != NULL) {
    //      array[i].value = realloc(array[i].value, hash_map->size_type);
    //    }

    hash_map->size = 0;
  }
}

void HashMapDestroy(HashMap **hash_map)
{
  if (*hash_map == NULL)
    return;

  HashMapItem* array = (*hash_map)->array;

  int i;
  for (i = 0; i < (*hash_map)->max_size; ++i) {
    if(array[i].value != NULL) {
      free(array[i].value);
      array[i].value = NULL;
    }
  }

  if (array != NULL) {
    free(array);
    array = NULL;
  }

  (*hash_map)->hash = NULL;
  (*hash_map)->size = 0;
  (*hash_map)->max_size = 0;

  free(*hash_map);
  *hash_map = NULL;
}
