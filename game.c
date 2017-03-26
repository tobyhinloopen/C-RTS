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
  game->map.size.x = map_height;

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

static void update_unit_behavior(Unit * unit, void * world_ptr) {
  World * world = (World*)world_ptr;
  Unit * closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
  Unit * closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);
  Factory * closest_friendly_factory = unit_behavior_find_closest_friendly_factory(unit, world, 32.0f);

  float unit_health = unit_health_percentage(unit);

  if(closest_friendly_factory != NULL)
    unit_behavior_move_away_from(unit, closest_friendly_factory->position);
  else if(closest_friendly_unit != NULL)
    unit_behavior_move_away_from(unit, closest_friendly_unit->position);
  else if(closest_enemy_unit != NULL && unit_health >= 0.5f)
    unit_behavior_set_target_position(unit, closest_enemy_unit->position, 120.0f);
  else if(closest_enemy_unit != NULL)
    unit_behavior_evasive_flee_from(unit, closest_enemy_unit->position);
  else
    unit_behavior_movement_stop(unit);

  if(closest_enemy_unit == NULL)
    unit_behavior_head_stop(unit);
  else if(unit_health < 0.2f && vector_distance(unit->position, closest_enemy_unit->position) < 480.0f)
    unit_behavior_overdrive(unit);
  else
    unit_behavior_head_engage_position(unit, closest_enemy_unit->position);
}

static Projectile * create_unit_projectile(Unit * unit, World * world) {
  Projectile * projectile = &world_entity_allocate(world, PROJECTILE)->projectile;
  projectile_initialize(projectile, unit->position,
    unit->direction + unit->head_direction + rand_rangef(-0.02f, 0.02f), unit->team_id);
  projectile->distance_remaining *= rand_rangef(0.9f, 1.1f);
  return projectile;
}

static void create_unit_projectiles(Unit * unit, World * world) {
  if(unit_is_firing(unit)) {
    while(unit->next_fire_interval < 0) {
      Projectile * projectile = create_unit_projectile(unit, world);
      projectile_update(projectile, -unit->next_fire_interval);
      unit->next_fire_interval += UNIT_FIRE_INTERVAL;
    }
  }
}

static void update_unit_entity(Entity * entity, void * world_ptr) {
  if(entity->type == UNIT) {
    World * world = (World*)world_ptr;
    create_unit_projectiles(&entity->unit, world);
    update_unit_behavior(&entity->unit, world);
  }
}

void game_update(Game * game) {
  game->current_time = SDL_GetTicks();
  game->delta = game->current_time - game->last_time;

  world_iterate_entities(&game->world, &game->world, update_unit_entity);

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
