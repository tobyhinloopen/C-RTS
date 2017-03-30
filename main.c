#include "test.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mod/event.h"
#include "mod/unit_projectile_spawn.h"
#include "mod/projectile_unit_impact.h"
#include "mod/unit_behavior.h"
#include "mod/random_spawn.h"
#include "mod/factory_spawn.h"
#include "mod/world_update.h"
#include "mod/camera_update.h"
#include "mod/render.h"

const float SIZE_X = 2048;
const float SIZE_Y = 2048;
const int SPAWN_POINTS_COUNT = 4;
const int MOD_COUNT = 8;
const int SHAPE_COUNT = 1;

int main(int argc, char **argv) {
  srand(time(NULL));

  test();

  Game game;
  game_initialize(&game, SPAWN_POINTS_COUNT, SHAPE_COUNT, SIZE_X, SIZE_Y, MOD_COUNT);

  game.map.spawn_points[0] = vector_create(SIZE_X * 0.2, SIZE_Y * 0.2);
  game.map.spawn_points[1] = vector_create(SIZE_X * 0.8, SIZE_Y * 0.2);
  game.map.spawn_points[2] = vector_create(SIZE_X * 0.8, SIZE_Y * 0.8);
  game.map.spawn_points[3] = vector_create(SIZE_X * 0.2, SIZE_Y * 0.8);

  Shape * shape = &game.map.shapes[0];
  shape_alloc(shape, 5);
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.60, SIZE_Y * 0.50));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.55));
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.55));
  shape_initialize(shape);

  game_add_module(&game, mod_event);
  game_add_module(&game, mod_unit_projectile_spawn);
  game_add_module(&game, mod_projectile_unit_impact);
  game_add_module(&game, mod_unit_behavior);
  game_add_module(&game, mod_factory_spawn);
  // game_add_module(&game, mod_random_spawn);
  game_add_module(&game, mod_world_update);
  game_add_module(&game, mod_camera_update);
  game_add_module(&game, mod_render);

  game.renderer.camera.x = SIZE_X / 2;
  game.renderer.camera.y = SIZE_Y / 2;

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);

  return 0;
}
