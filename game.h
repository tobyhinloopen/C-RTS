#ifndef GAME_H
#define GAME_H

typedef struct Game Game;

#include "world.h"
#include "map.h"
#include "renderer.h"
#include "vector3.h"
#include "grid.h"
#include "kdtree.h"
#include "scalable_grid.h"
#include "team_id.h"
#include "rand_range.h"
#include "bktree.h"
#include <time.h>

#define GAME_MODULE_DURATION_LENGTH 32

typedef struct GameModule GameModule;

struct Game {
  int is_quit_requested;
  int is_window_resized;
  Renderer renderer;
  World world;
  Map map;
  KDTree units_kdtrees[TEAM_COUNT];
  KDTree factories_kdtrees[TEAM_COUNT];
  ScalableGrid scalable_grid;
  RandRangeSeed seed;
#ifdef CONFIG_BKTREE_ENABLED
  BKTree units_bktrees[TEAM_COUNT];
#endif

  unsigned int start_time;
  unsigned int current_time;
  unsigned int delta;
  unsigned int last_time;
  unsigned int last_spawn_time;

  clock_t cumulative_update_duration;
  size_t update_count;

  Vector3 camera_movement;
  struct GameModule * modules;
  size_t modules_count;
  size_t modules_capacity;
};

struct GameModule {
  char * name;
  clock_t duration_initialize;
  clock_t duration_deinitialize;
  clock_t duration_update [GAME_MODULE_DURATION_LENGTH];
  int duration_update_index;
  void (* initialize)(Game * game);
  void (* tick)(Game * game);
  void (* update)(Game * game, unsigned int delta_since_tick);
  void (* deinitialize)(Game * game);
};

void game_initialize(Game * game, int spawn_points_count, int shapes_count, float map_width, float map_height, size_t mod_capacity);
void game_add_module(Game * game, char * name, void (* mod_fn)(GameModule *));
void game_update(Game * game);
void game_update_time(Game * game, unsigned int current_time);
void game_deinitialize(Game * game);

#endif
