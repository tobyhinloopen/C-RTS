#include "game.h"

#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include "unit.h"
#include "projectile.h"
#include "test.h"
#include "world.h"
#include "pi.h"
#include "vector.h"
#include "vector3.h"
#include "unit/behavior.h"
#include <math.h>
#include <assert.h>

const int TEAM_COUNT = 4;
const int TEAM_COLOR[TEAM_COUNT] = { 0xFF0000, 0x00CC00, 0x4444FF, 0xCC8800 };

const int UNIT_SPAWN_INTERVAL_MS = 20;
const int UNIT_SPAWN_MAX_GROUP_SIZE = 8;
const int UNIT_MAX_SPAWN_COUNT = 400;

void game_initialize(Game * game, size_t mod_capacity) {
  game->modules = malloc(sizeof(GameModule) * mod_capacity);
  game->modules_count = 0;
  game->modules_capacity = mod_capacity;

  game->is_quit_requested = 1;
  game->is_window_resized = 0;
  game->camera_movement = (Vector3) { 0.0f, 0.0f, 0.0f };

  world_initialize(&game->world);

  SDL_InitSubSystem(SDL_INIT_TIMER);
  game->start_time = SDL_GetTicks();
  game->last_time = game->start_time;
  game->last_spawn_time = game->last_time;

  srand(time(NULL));
}

void game_add_module(Game * game, void (*mod_fn)(GameModule *)) {
  assert(game->modules_count < game->modules_capacity);

  GameModule * game_module = &game->modules[game->modules_count++];
  mod_fn(game_module);
  game_module->initialize(game);
}

static void update_unit_behavior(Unit * unit, void * world_ptr) {
  World * world = (World*)world_ptr;
  Unit * closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
  Unit * closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);

  float unit_health = unit_health_percentage(unit);

  if(closest_friendly_unit != NULL)
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

static float rand_rangef(float min, float max) {
  return min + ((double)rand() / RAND_MAX) * (max - min);
}

static float rand_rangef_pow2(float min, float max) {
  const float magnitude = (max - min)/2;
  const float magnitude_sq = magnitude * magnitude;
  const float result = rand_rangef(-magnitude_sq, magnitude_sq);
  return sqrtf(result < 0.0f ? -result : result) * (result < 0.0f ? -1.0f : 1.0f);
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

static void destroy_unit_touching_projectile(Entity * entity, void * projectile_ptr) {
  Unit * unit = &entity->unit;
  Projectile * projectile = (Projectile*)projectile_ptr;
  if(entity->type == UNIT
  && unit->team_id != projectile->team_id
  && projectile->distance_remaining > 0
  && vector_distance(projectile->position, unit->position) < 12.0f) {
    unit->health -= projectile_damage(projectile);
    projectile->distance_remaining = 0;
  }
}

static void update_projectile_entity(Entity * entity, void * world_ptr) {
  if(entity->type == PROJECTILE) {
    world_iterate_entities((World*)world_ptr, &entity->projectile, destroy_unit_touching_projectile);
  }
}

static void update_unit_entity(Entity * entity, void * world_ptr) {
  if(entity->type == UNIT) {
    World * world = (World*)world_ptr;
    create_unit_projectiles(&entity->unit, world);
    update_unit_behavior(&entity->unit, world);
  }
}

static int rand_rangei(int min, int max) {
  return rand_rangef(min, max);
}

static void setup_unit(Unit * unit, int team_offset, float x, float y) {
  unit_initialize(unit);
  unit->direction = rand_rangef(0, PI2);
  unit->team_id = TEAM_COLOR[team_offset];
  unit->position.x = x + rand_rangef_pow2(-80.0f, 80.0f);
  unit->position.y = y + rand_rangef_pow2(-80.0f, 80.0f);
}

static void increment_for_unit_entity(Entity * entity, void * count_ptr) {
  int * count = (int*)count_ptr;
  if(entity->type == UNIT)
    (*count)++;
}

static int world_count_units(World * world) {
  int count = 0;
  world_iterate_entities(world, &count, increment_for_unit_entity);
  return count;
}

static int is_game_unit_spawn_interval_passed(Game * game, unsigned int current_time) {
  return UNIT_SPAWN_INTERVAL_MS > 0 && game->last_spawn_time + UNIT_SPAWN_INTERVAL_MS <= current_time;
}

static void game_spawn_next_unit_group(Game * game) {
  game->last_spawn_time += UNIT_SPAWN_INTERVAL_MS;
  int team_offset = rand_rangei(0, TEAM_COUNT);
  float x = rand_rangef_pow2(-640.0f, 640.0f);
  float y = rand_rangef_pow2(-640.0f, 640.0f);
  int world_unit_count = world_count_units(&game->world);
  for(int unit_count = rand_rangei(1, UNIT_SPAWN_MAX_GROUP_SIZE); unit_count >= 0; --unit_count)
    if(world_unit_count++ < UNIT_MAX_SPAWN_COUNT)
      setup_unit(&world_entity_allocate(&game->world, UNIT)->unit, team_offset, x, y);
}

void game_update(Game * game) {
  unsigned int current_time = SDL_GetTicks();
  unsigned int delta = current_time - game->last_time;

  while(is_game_unit_spawn_interval_passed(game, current_time))
    game_spawn_next_unit_group(game);

  world_iterate_entities(&game->world, &game->world, update_projectile_entity);
  world_iterate_entities(&game->world, &game->world, update_unit_entity);

  for(size_t i = 0; i < game->modules_count; i++)
    game->modules[i].update(game, delta);

  game->last_time = current_time;
}

void game_deinitialize(Game * game) {
  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&game->world);

  for(size_t i = 0; i < game->modules_count; i++)
    game->modules[i].deinitialize(game);

  free(game->modules);
}
