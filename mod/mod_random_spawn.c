#include "mod_random_spawn.h"

#include "../pi.h"
#include "../rand_range.h"
#include "../team_id.h"

const int UNIT_SPAWN_INTERVAL_MS = 1000;
const int UNIT_SPAWN_MAX_GROUP_SIZE = 4;
const int UNIT_MAX_SPAWN_COUNT = 400;
const int UNIT_INITIAL_SPAWN_GROUP_COUNT = 4;

const float RANGE_X = 1280.0f;
const float RANGE_Y = 1280.0f;
const float JITTER_X = 80.0f;
const float JITTER_Y = 80.0f;

static int is_game_unit_spawn_interval_passed(Game * game, unsigned int current_time) {
  return UNIT_SPAWN_INTERVAL_MS > 0 && game->last_spawn_time + UNIT_SPAWN_INTERVAL_MS <= current_time;
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

static void setup_unit(Unit * unit, RandRangeSeed * seed, int team_offset, float x, float y) {
  unit_initialize(unit);
  unit->direction = rand_rangef(seed, 0, PI2);
  unit->team_id = team_offset;
  unit->position.x = x + rand_rangef_pow2(seed, -JITTER_X, JITTER_X);
  unit->position.y = y + rand_rangef_pow2(seed, -JITTER_Y, JITTER_Y);
}

static void game_spawn_next_unit_group(Game * game) {
  game->last_spawn_time += UNIT_SPAWN_INTERVAL_MS;
  int team_offset = rand_rangei(&game->seed, 0, TEAM_COUNT);
  float x = rand_rangef_pow2(&game->seed, -RANGE_X, RANGE_X);
  float y = rand_rangef_pow2(&game->seed, -RANGE_Y, RANGE_Y);
  int world_unit_count = world_count_units(&game->world);
  for(int unit_count = rand_rangei(&game->seed, 1, UNIT_SPAWN_MAX_GROUP_SIZE); unit_count >= 0; --unit_count)
    if(world_unit_count++ < UNIT_MAX_SPAWN_COUNT)
      setup_unit(&world_entity_allocate(&game->world, UNIT)->unit, &game->seed, team_offset, x, y);
}

static void mod_random_spawn_initialize(Game * game, void * arg) {
  for(int i=0; i<UNIT_INITIAL_SPAWN_GROUP_COUNT; ++i)
    game_spawn_next_unit_group(game);
  game->last_spawn_time = game->start_time;
}

static void mod_random_spawn_update(Game * game, unsigned int delta, void * arg) {
  while(is_game_unit_spawn_interval_passed(game, game->current_time))
    game_spawn_next_unit_group(game);
}

void mod_random_spawn(GameModule * mod) {
  mod->initialize = mod_random_spawn_initialize;
  mod->update = mod_random_spawn_update;
}
