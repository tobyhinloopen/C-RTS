#ifndef GAME_H
#define GAME_H

#include "world.h"
#include "map.h"
#include "renderer.h"
#include "vector3.h"

typedef struct Game Game;
typedef struct GameModule GameModule;

struct Game {
  int is_quit_requested;
  int is_window_resized;
  Renderer renderer;
  World world;
  Map map;

  unsigned int start_time;
  unsigned int current_time;
  unsigned int delta;
  unsigned int last_time;
  unsigned int last_spawn_time;

  Vector3 camera_movement;
  struct GameModule * modules;
  size_t modules_count;
  size_t modules_capacity;
};

struct GameModule {
  void (* initialize)(Game * game);
  void (* tick)(Game * game);
  void (* update)(Game * game, unsigned int delta_since_tick);
  void (* deinitialize)(Game * game);
};

void game_initialize(Game * game, int spawn_points_count, int shapes_count, float map_width, float map_height, size_t mod_capacity);
void game_add_module(Game * game, void (* mod_fn)(GameModule *));
void game_update(Game * game);
void game_update_time(Game * game, unsigned int current_time);
void game_deinitialize(Game * game);

#endif
