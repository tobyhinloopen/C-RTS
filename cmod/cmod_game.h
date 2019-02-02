#ifndef CMOD_GAME_H
#define CMOD_GAME_H

#include "../client.h"
#include "../game.h"

typedef struct {
  int spawn_points_count;
  int shapes_count;
  float map_width;
  float map_height;
  size_t mod_capacity;
  void * init_data;
  void (* init)(Game * game, void * init_data);
} CMODGameData;

void cmod_game(const Client *, ClientModule *, void * cmod_game_data);

#endif
