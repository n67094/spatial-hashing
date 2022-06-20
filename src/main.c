#include "core/list.h"
#include "tigr.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "./core/log.h"
#include "./core/spatial-hash.h"
#include "./core/types.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// spatial hashing stuff
#define CELL_SIZE 32

#define MAX_COLLISIONS 10

#define PLAYER_SPEED 20

typedef struct Object {
  int id;
  Rectangle collision;
  TPixel color;
} Object;

Object objects[MAX_COLLISIONS];

Object player;
float player_x = {(SCREEN_WIDTH >> 1) - (CELL_SIZE >> 1)};
float player_y = {(SCREEN_HEIGHT >> 1) - (CELL_SIZE >> 1)};

SpatialHash *spatial_hash;

static int CollisionCompare(void *a, void *b) {
  int typed_a = *(int *)a;
  int typed_b = *(int *)b;

  if (typed_a == typed_b)
    return 0;

  return -1;
}

Tigr *screen = NULL;

void update(float dt) 
{
  //move player
 if (tigrKeyHeld(screen, TK_LEFT))
   player_x -= PLAYER_SPEED * dt;
 else if(tigrKeyHeld(screen, TK_RIGHT))
   player_x += PLAYER_SPEED *dt;
 else if(tigrKeyHeld(screen, TK_UP))
   player_y -= PLAYER_SPEED * dt;
 else if(tigrKeyHeld(screen, TK_DOWN))
   player_y += PLAYER_SPEED * dt;

 player.collision.x = player_x;
 player.collision.y = player_y;

 // check collision
 SpatialHashClear(spatial_hash);

 int i;
 for (i = 0; i < MAX_COLLISIONS; ++i) {
   SpatialHashRegister(spatial_hash, objects[i].id, objects[i].collision);
  }
}

void draw(Tigr *screen)
{
  int i;

  List *nearby_collision =
      SpatialHashNearby(spatial_hash, player.id, player.collision);

  // draw rectangle
  for(i = 0; i < MAX_COLLISIONS; ++i) {

    TPixel final_color = objects[i].color;

    if (ListContains(nearby_collision, &objects[i].id, CollisionCompare)) {
      final_color = tigrRGB(0, 255, 0);
    }

    tigrRect(screen,
             objects[i].collision.x,
             objects[i].collision.y,
             objects[i].collision.w,
             objects[i].collision.h,
             final_color);
  }

  // draw player
  tigrRect(screen,
           player.collision.x,
           player.collision.y,
           player.collision.w,
           player.collision.h,
           player.color);

  // draw row
  int row = (SCREEN_HEIGHT + (CELL_SIZE - 1)) / CELL_SIZE; // ciel with integer
  for (i = 0; i < row + 1; ++i) {
    tigrLine(screen,
             0,
             i * CELL_SIZE,
             SCREEN_WIDTH,
             i * CELL_SIZE,
             tigrRGB(255, 255, 255));
  }

  // draw col
  int col = (SCREEN_WIDTH + (CELL_SIZE - 1)) / CELL_SIZE; // ciel with integer
  for (i = 0; i < col; ++i) {
    tigrLine(screen,
             i * CELL_SIZE,
             0,
             i * CELL_SIZE,
             SCREEN_HEIGHT,
             tigrRGB(255, 255, 255));
  }

  ListDestroy(&nearby_collision);
}

int main(int argc, char *argv[])
{
  // create rectangle
  int i;
  for (i = 0; i < MAX_COLLISIONS; ++i) {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;

    objects[i] = (Object){
        i, // id 0 to 9
        {x, y, 16, 16},
        tigrRGB(0, 0, 255)
    };
  }

  player = (Object){
      10, // id 10
      {(SCREEN_WIDTH >> 1) - (CELL_SIZE >> 1),
                 (SCREEN_HEIGHT >> 1) - (CELL_SIZE >> 1),
                 16, 16},
      tigrRGB(255, 0, 0)
  };

  spatial_hash = SpatialHashCreate(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE);

  screen = tigrWindow(
      SCREEN_WIDTH, SCREEN_HEIGHT, "Spatial hashing", TIGR_AUTO | TIGR_2X);

  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
    float dt = tigrTime();
    update(dt);

    tigrClear(screen, tigrRGB(0x00, 0x00, 0x00));

    draw(screen);

    tigrUpdate(screen);
  }

  tigrFree(screen);

  // FIXME this run a segmant fault
  SpatialHashDestroy(&spatial_hash);

  return 0;
}
