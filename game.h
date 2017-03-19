#ifndef GAME_H
#define GAME_H

#include "world.h"
#include "renderer.h"
#include "vector3.h"

typedef struct {
  int is_quit_requested;
  Renderer renderer;
  World world;
  unsigned int start_time;
  unsigned int last_time;
  unsigned int last_spawn_time;
  Vector3 camera_movement;
} Game;

void game_initialize(Game * game);
int game_is_quit_requested(Game * game);
void game_update(Game * game);
void game_deinitialize(Game * game);

#endif
