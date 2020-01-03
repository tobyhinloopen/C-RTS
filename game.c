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
#include <string.h>

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

  game->command_position_set = 0;
  vector_initialize(&game->command_position);

  SDL_InitSubSystem(SDL_INIT_TIMER);

  game->delta = 0;
  game->start_time = SDL_GetTicks();
  game->current_time = game->start_time;
  game->last_time = game->start_time;
  game->last_spawn_time = 0;
  game->seed = 0;

  game->cumulative_update_duration = 0;
  game->update_count = 0;
}

static void noop_game(Game * game, void * arg) {}
static void noop_game_delta(Game * game, unsigned int delta, void * arg) {}
static size_t alloc_zero(Game * game) { return 0; }

static void game_clear_module(GameModule * mod) {
  mod->duration_initialize = 0;
  mod->duration_deinitialize = 0;
  mod->duration_update_index = 0;
  memset(&mod->duration_update, 0, sizeof(mod->duration_update));
  mod->alloc_size = alloc_zero;
  mod->initialize = noop_game;
  mod->tick = noop_game;
  mod->update = noop_game_delta;
  mod->deinitialize = noop_game;
}

static void game_initialize_module(GameModule * mod, Game * game, char * name, void (*mod_fn)(GameModule *)) {
  game_clear_module(mod);
  mod->name = name;
  mod_fn(mod);

  clock_t start = clock();
  size_t size = mod->alloc_size(game);
  mod->data = size > 0 ? malloc(size) : NULL;
  assert(size > 0 && mod->data != NULL || size == 0);
  mod->initialize(game, mod->data);
  mod->duration_initialize = clock() - start;
}

void game_add_module(Game * game, char * name, void (*mod_fn)(GameModule *)) {
  assert(game->modules_count < game->modules_capacity);
  game_initialize_module(&game->modules[game->modules_count++], game, name, mod_fn);
}

void game_update(Game * game) {
  game_update_time(game, SDL_GetTicks());
}

void game_update_time(Game * game, unsigned int current_time) {
  assert(current_time >= game->current_time);
  game->current_time = current_time;
  game->delta = game->current_time - game->last_time;
  game->update_count++;
  clock_t update_start_time = clock();

  for(size_t i = 0; i < game->modules_count; i++) {
    GameModule * mod = &game->modules[i];
    if (game->delta == 0 && strncmp(mod->name, "mod_event", 9))
      continue;

    clock_t start = clock();
    mod->update(game, game->delta, mod->data);
    mod->duration_update[mod->duration_update_index++] = clock() - start;
    mod->duration_update_index %= GAME_MODULE_DURATION_LENGTH;
  }

  game->cumulative_update_duration += clock() - update_start_time;
  game->last_time = game->current_time;
}

void game_deinitialize(Game * game) {
  for(size_t i = 0; i < game->modules_count; i++) {
    GameModule * mod = &game->modules[i];

    clock_t start = clock();
    mod->deinitialize(game, mod->data);
    if (mod->data != NULL) {
      free(mod->data);
    }
    mod->duration_deinitialize = clock() - start;
  }

  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&game->world);
  map_deinitialize(&game->map);

  free(game->modules);
  game->modules = NULL;
}
