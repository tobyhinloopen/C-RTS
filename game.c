#include "game.h"

#include <SDL2/SDL.h>
#include "unit.h"
#include "projectile.h"
#include "world.h"
#include "vector.h"
#include "vector3.h"
#include "unit/behavior.h"
#include <assert.h>
#include "rand_range.h"

void game_initialize(Game * game, int spawn_points_count, int shapes_count, float map_width, float map_height, size_t mod_capacity) {
  game->modules = malloc(sizeof(GameModule) * mod_capacity);
  game->modules_count = 0;
  game->modules_capacity = mod_capacity;

  game->is_quit_requested = 1;
  game->is_window_resized = 0;
  game->camera_movement = (Vector3) { 0.0f, 0.0f, 0.0f };

  map_initialize(&game->map, spawn_points_count, shapes_count);
  game->map.size.x = map_width;
  game->map.size.y = map_height;

  world_initialize(&game->world);

  SDL_InitSubSystem(SDL_INIT_TIMER);

  game->delta = 0;
  game->start_time = SDL_GetTicks();
  game->current_time = game->start_time;
  game->last_time = game->start_time;
  game->last_spawn_time = 0;
}

static void noop_game(Game * game) {}
static void noop_game_delta(Game * game, unsigned int delta) {}

static void game_clear_module(GameModule * mod) {
  mod->initialize = noop_game;
  mod->tick = noop_game;
  mod->update = noop_game_delta;
  mod->deinitialize = noop_game;
}

static void game_initialize_module(GameModule * mod, Game * game, void (*mod_fn)(GameModule *)) {
  game_clear_module(mod);
  mod_fn(mod);
  mod->initialize(game);
}

void game_add_module(Game * game, void (*mod_fn)(GameModule *)) {
  assert(game->modules_count < game->modules_capacity);
  game_initialize_module(&game->modules[game->modules_count++], game, mod_fn);
}

void game_update(Game * game) {
  game->current_time = SDL_GetTicks();
  game->delta = game->current_time - game->last_time;

  for(size_t i = 0; i < game->modules_count; i++)
    game->modules[i].update(game, game->delta);

  game->last_time = game->current_time;
}

void game_deinitialize(Game * game) {
  for(size_t i = 0; i < game->modules_count; i++)
    game->modules[i].deinitialize(game);

  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&game->world);
  map_deinitialize(&game->map);

  free(game->modules);
  game->modules = NULL;
}
