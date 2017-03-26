#include "test.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mod/event.h"
#include "mod/projectile_unit_impact.h"
#include "mod/random_spawn.h"
#include "mod/render.h"

float SIZE_X = 2048;
float SIZE_Y = 2048;

int main(int argc, char **argv) {
  srand(time(NULL));

  test();

  Game game;
  game_initialize(&game, 4, 1, SIZE_X, SIZE_Y, 4);

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
  game_add_module(&game, mod_projectile_unit_impact);
  game_add_module(&game, mod_random_spawn);
  game_add_module(&game, mod_render);

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);

  return 0;
}
