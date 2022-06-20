#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "log.h"
#include "spatial-hash.h"
#include "types.h"

static int SpatialHashCellIdCompare(void *a, void *b)
{
  assert(a != NULL);
  assert(b != NULL);

  int typed_a = *(int *)a;
  int typed_b = *(int *)b;

  if (typed_a == typed_b)
    return 0;

  return -1;
}

static void
SpatialHashCellId(SpatialHash *spatial_hash, List *cell_ids, int x, int y)
{
  assert(spatial_hash != NULL);
  assert(cell_ids != NULL);

  int cell_size = spatial_hash->cell_size;
  int buckets_size = spatial_hash->buckets_size;
  int row = spatial_hash->row;

  int cell_id = (x / cell_size) + (y / cell_size) * row;

  if (cell_id >= 0 && cell_id < buckets_size &&
      !ListContains(cell_ids, &cell_id, SpatialHashCellIdCompare)) {
    ListPush(cell_ids, &cell_id);
  }
}

// Todo to optimise I can return an array and a bigger sprite will be composed
// of more than one rectangle collision ?
// or if not possible do some calculation to find cells if a rectangle is bigger
// than cell_size
static List *SpatialHashCellIds(SpatialHash *spatial_hash, Rectangle rectangle)
{
  List *cell_ids = ListCreate(sizeof(int));

  // top left
  SpatialHashCellId(spatial_hash, cell_ids, rectangle.x, rectangle.y);

  // top right
  SpatialHashCellId(
      spatial_hash, cell_ids, rectangle.x + rectangle.w, rectangle.y);

  // bottom left
  SpatialHashCellId(
      spatial_hash, cell_ids, rectangle.x, rectangle.y + rectangle.h);

  // bottom right
  SpatialHashCellId(spatial_hash,
                    cell_ids,
                    rectangle.x + rectangle.w,
                    rectangle.y + rectangle.h);

  return cell_ids;
}

SpatialHash *
SpatialHashCreate(int screen_width, int screen_height, int cell_size)
{
  assert(screen_width > 0);
  assert(screen_height > 0);
  assert(cell_size > 0);

  SpatialHash *spatial_hash = malloc(sizeof(SpatialHash));
  if (spatial_hash == NULL) {
    LOG_ERROR("allocation");
    return NULL;
  }

  // performent way of ciel if @screen_width is != 0
  int row = 1 + ((screen_width - 1) / cell_size);
  int col = 1 + ((screen_height - 1) / cell_size);
  int buckets_size = row * col;

  spatial_hash->row = row;
  spatial_hash->col = col;
  spatial_hash->cell_size = cell_size;
  spatial_hash->buckets_size = buckets_size;
  spatial_hash->buckets = calloc(buckets_size, sizeof(List));

  int i;
  for (i = 0; i < buckets_size; ++i) {
    spatial_hash->buckets[i] = ListCreate(sizeof(int));
  }

  return spatial_hash;
}

void SpatialHashRegister(SpatialHash *spatial_hash, int id, Rectangle rectangle)
{
  assert(spatial_hash != NULL);
  assert(id >= 0);

  List *cell_ids = SpatialHashCellIds(spatial_hash, rectangle);

  // if no cells for the rectangle (off screen ?)
  if (cell_ids->size == 0)
    return;

  ListItem *pointer;
  for (pointer = cell_ids->tail; pointer != NULL; pointer = pointer->next) {
    int cell_id = *(int *)pointer->value;
    ListPush(spatial_hash->buckets[cell_id], &id);
  }

  ListDestroy(&cell_ids);
}

// todo remove id it is not used
List *SpatialHashNearby(SpatialHash *spatial_hash, int id, Rectangle rectangle)
{
  List *cell_ids = SpatialHashCellIds(spatial_hash, rectangle);

  List *nearby = ListCreate(sizeof(int));

  // if no nearby collision
  if (cell_ids->size == 0)
    return nearby;

  ListItem *pointer;
  for (pointer = cell_ids->tail; pointer != NULL; pointer = pointer->next) {
    int cell_id = *(int *)pointer->value;
    ListPushAll(nearby, spatial_hash->buckets[cell_id]);
  }

  ListDestroy(&cell_ids);

  return nearby;
}

void SpatialHashClear(SpatialHash *spatial_hash)
{
  assert(spatial_hash != NULL);

  int i;
  for (i = 0; i < spatial_hash->buckets_size; ++i) {
    List *list = spatial_hash->buckets[i];
    ListDestroy(&list);
    spatial_hash->buckets[i] = ListCreate(sizeof(int));
  }
}

void SpatialHashDestroy(SpatialHash **spatial_hash)
{
  assert(*spatial_hash != NULL);

  int i;
  for (i = 0; i < (*spatial_hash)->buckets_size; ++i) {
    ListDestroy(&(*spatial_hash)->buckets[i]);
  }
  free((*spatial_hash)->buckets);
  (*spatial_hash)->buckets = NULL;

  free(*spatial_hash);
  spatial_hash = NULL;
}
