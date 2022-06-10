#ifndef CORE_SPATIAL_HASH_H
#define CORE_SPATIAL_HASH_H

#include "list.h"
#include "types.h"

typedef struct SpatialHash {
  int row;
  int col;
  int cell_size;
  int buckets_size;
  List **buckets; // on buckets per cell
} SpatialHash;

SpatialHash *
SpatialHashCreate(int screen_width, int screen_height, int cell_size);

void SpatialHashClear(SpatialHash *spatial_hash);

void SpatialHashRegister(SpatialHash *spatial_hash, int id, Rectangle rect);

List *SpatialHashNearby(SpatialHash *spatial_hash, int id, Rectangle rectangle);

void SpatialHashDestroy(SpatialHash **Spatial_hash);

#endif
