#include "cmod_game.h"
#include "assert.h"

static int cmod_game_update(const Client * client, void * game_ptr) {
  assert(game_ptr);
  Game * game = (Game*)game_ptr;
  game_update_time(game, client->current_time);
  return !game->is_quit_requested;
}

static void cmod_game_deinit(const Client * client, void * game_ptr) {
  assert(game_ptr);
  Game * game = (Game*)game_ptr;
  game_deinitialize(game);
  free(game_ptr);
}

void cmod_game(const Client * client, ClientModule * mod, void * data_ptr) {
  assert(data_ptr);
  CMODGameData * data = (CMODGameData*)data_ptr;
  Game * game = malloc(sizeof(Game));
  game_initialize(game, data->spawn_points_count, data->shapes_count, data->map_width, data->map_height, data->mod_capacity);
  if (data->init) {
    data->init(game, data->init_data);
  }
  mod->name = "cmod_game";
  mod->data = game;
  mod->update = cmod_game_update;
  mod->deinit = cmod_game_deinit;
}
