#include "test.h"
#include "game.h"
#include "benchmark.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mod/event.h"
#include "mod/unit_projectile_spawn.h"
#include "mod/projectile_unit_impact.h"
#include "mod/unit_behavior.h"
#include "mod/factory_spawn.h"
#include "mod/world_update.h"
#include "mod/camera_update.h"
#include "mod/render.h"

const float SIZE_X = 2048;
const float SIZE_Y = 2048;
const int SPAWN_POINTS_COUNT = 4;
const int MOD_COUNT = 8;
const int SHAPE_COUNT = 1;

const unsigned int BENCHMARK_INTERVAL_MS = 0x0000F;
const unsigned int BENCHMARK_DURATION_MS = 0x1FFFF;

static void make_game(Game * game) {
  game_initialize(game, SPAWN_POINTS_COUNT, SHAPE_COUNT, SIZE_X, SIZE_Y, MOD_COUNT);

  game->map.spawn_points[0] = vector_create(SIZE_X * 0.2, SIZE_Y * 0.2);
  game->map.spawn_points[1] = vector_create(SIZE_X * 0.8, SIZE_Y * 0.2);
  game->map.spawn_points[2] = vector_create(SIZE_X * 0.8, SIZE_Y * 0.8);
  game->map.spawn_points[3] = vector_create(SIZE_X * 0.2, SIZE_Y * 0.8);

  Shape * shape = &game->map.shapes[0];
  shape_alloc(shape, 5);
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.60, SIZE_Y * 0.50));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.55));
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.55));
  shape_initialize(shape);

  game_add_module(game, mod_event);
  game_add_module(game, mod_unit_projectile_spawn);
  game_add_module(game, mod_projectile_unit_impact);
  game_add_module(game, mod_unit_behavior);
  game_add_module(game, mod_factory_spawn);
  game_add_module(game, mod_world_update);
  game_add_module(game, mod_camera_update);
  game_add_module(game, mod_render);

  game->renderer.camera.x = SIZE_X / 2;
  game->renderer.camera.y = SIZE_Y / 2;
}

static void benchmark() {
  Game game;
  srand(0);
  make_game(&game);
  clock_t start_time = clock();
  benchmark_game(&game, BENCHMARK_INTERVAL_MS, BENCHMARK_DURATION_MS);
  double duration_s = (double)(clock() - start_time) / CLOCKS_PER_SEC;
  game_deinitialize(&game);
  int frames_count = BENCHMARK_DURATION_MS / BENCHMARK_INTERVAL_MS;
  printf("Benchmark: %.2fs (%.2f FPS)\n", duration_s, frames_count / duration_s);
}

int main(int argc, char **argv) {
  test();
  benchmark();

  Game game;
  srand(time(NULL));
  make_game(&game);

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);

  return 0;
}
