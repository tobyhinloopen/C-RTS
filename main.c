#include "game.h"
#include "config.h"
#include "benchmark.h"
#include "test.h"
#include "team_id.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mod/mod_scalable_grid.h"
#include "mod/mod_kdtree.h"
#include "mod/mod_closest_enemy_unit.h"
#include "mod/mod_closest_friendly_unit.h"
#include "mod/mod_closest_factory.h"
#include "mod/mod_event.h"
#include "mod/mod_unit_projectile_spawn.h"
#include "mod/mod_projectile_unit_impact.h"
#include "mod/mod_unit_behavior.h"
#include "mod/mod_factory_spawn.h"
#include "mod/mod_world_update.h"
#include "mod/mod_camera_update.h"
#include "mod/mod_render.h"
#include "mod/mod_print_performance.h"
#include "mod/mod_bktree.h"

#ifdef CONFIG_BENCHMARK_ENABLED
#define CONFIG_MAKE_GAME
#endif
#ifdef CONFIG_GAME_ENABLED
#define CONFIG_MAKE_GAME
#endif

#define MOD_COUNT 14
#define SHAPE_COUNT 1

#ifdef CONFIG_MAKE_GAME

static void make_game(Game * game, RandRangeSeed seed) {
  game_initialize(game, SPAWN_POINTS_COUNT, SHAPE_COUNT, SIZE_X, SIZE_Y, MOD_COUNT);
  game->seed = seed;

  for (int i = 0; i < SPAWN_POINTS_COUNT; i++) {
    int xy_offset = (i / (TEAM_COUNT - 1));
    int x_offset = xy_offset / FACTORY_ROWS;
    int y_offset = xy_offset % FACTORY_ROWS;

    Vector spawn = {SPAWN_OFFSET, SPAWN_OFFSET};
    spawn.x += SPAWN_DISTANCE * x_offset;
    spawn.y += SPAWN_DISTANCE * y_offset;
    Vector team_mp = TEAM_SPAWN[1 + i % (TEAM_COUNT - 1)];
    spawn.x *= team_mp.x;
    spawn.y *= team_mp.y;
    spawn.x += 0.5;
    spawn.y += 0.5;
    spawn.x *= SIZE_X;
    spawn.y *= SIZE_Y;
    game->map.spawn_points[i] = spawn;
  }

  Shape * shape = &game->map.shapes[0];
  shape_alloc(shape, 5);
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.45));
  shape_add(shape, vector_create(SIZE_X * 0.60, SIZE_Y * 0.50));
  shape_add(shape, vector_create(SIZE_X * 0.55, SIZE_Y * 0.55));
  shape_add(shape, vector_create(SIZE_X * 0.45, SIZE_Y * 0.55));
  shape_initialize(shape);

  game_add_module(game, "mod_event", mod_event);
#ifdef CONFIG_SCALABLE_GRID_ENABLED
  game_add_module(game, "mod_scalable_grid", mod_scalable_grid);
#endif
#ifdef CONFIG_BKTREE_ENABLED
  game_add_module(game, "mod_bktree", mod_bktree);
#endif
  game_add_module(game, "mod_kdtree", mod_kdtree);
  game_add_module(game, "mod_factory_spawn", mod_factory_spawn);
  game_add_module(game, "mod_closest_enemy_unit", mod_closest_enemy_unit);
  game_add_module(game, "mod_closest_friendly_unit", mod_closest_friendly_unit);
  game_add_module(game, "mod_closest_factory", mod_closest_factory);
  game_add_module(game, "mod_unit_projectile_spawn", mod_unit_projectile_spawn);
  game_add_module(game, "mod_projectile_unit_impact", mod_projectile_unit_impact);
  game_add_module(game, "mod_unit_behavior", mod_unit_behavior);
  game_add_module(game, "mod_world_update", mod_world_update);
  game_add_module(game, "mod_camera_update", mod_camera_update);
  game_add_module(game, "mod_render", mod_render);
#ifdef CONFIG_PRINT_PERFORMANCE_ENABLED
  game_add_module(game, "mod_print_performance", mod_print_performance);
#endif

  game->renderer.camera.x += SIZE_X / 2;
  game->renderer.camera.y += SIZE_Y / 2;
}
#endif

#ifdef CONFIG_BENCHMARK_ENABLED
static void benchmark() {
  Game game;
  make_game(&game, 0);
  clock_t start_time = clock();
  benchmark_game(&game, BENCHMARK_INTERVAL_MS, BENCHMARK_DURATION_MS);
  double duration_s = (double)(clock() - start_time) / CLOCKS_PER_SEC;
  int frames_count = BENCHMARK_DURATION_MS / BENCHMARK_INTERVAL_MS;
  if(game.is_quit_requested)
    printf("Note: Benchmark was aborted!\n");
  printf("\n\nBenchmark: %.2fs (%.2f FPS)\n\n\n", duration_s, frames_count / duration_s);
  while(!game.is_quit_requested)
    game_update_time(&game, game.current_time);
  game_deinitialize(&game);
}
#endif

#ifdef CONFIG_GAME_ENABLED
static void run_game() {
  Game game;
  make_game(&game, time(NULL));

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);
}
#endif

int main(int argc, char **argv) {
#ifdef CONFIG_TEST_ENABLED
  test();
#endif
#ifdef CONFIG_BENCHMARK_ENABLED
  benchmark();
#endif
#ifdef CONFIG_GAME_ENABLED
  run_game();
#endif
  return 0;
}
