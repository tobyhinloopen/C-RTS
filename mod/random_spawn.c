#include "random_spawn.h"

#include "../pi.h"
#include "../rand_range.h"

const int TEAM_COUNT = 4;
const int TEAM_COLOR[TEAM_COUNT] = { 0xFF0000, 0x00CC00, 0x4444FF, 0xCC8800 };

const int UNIT_SPAWN_INTERVAL_MS = 20;
const int UNIT_SPAWN_MAX_GROUP_SIZE = 8;
const int UNIT_MAX_SPAWN_COUNT = 400;

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

static void setup_unit(Unit * unit, int team_offset, float x, float y) {
  unit_initialize(unit);
  unit->direction = rand_rangef(0, PI2);
  unit->team_id = TEAM_COLOR[team_offset];
  unit->position.x = x + rand_rangef_pow2(-80.0f, 80.0f);
  unit->position.y = y + rand_rangef_pow2(-80.0f, 80.0f);
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

static void mod_random_spawn_update(Game * game, unsigned int delta) {
  while(is_game_unit_spawn_interval_passed(game, game->current_time))
    game_spawn_next_unit_group(game);
}

static void mod_random_spawn_initialize(Game * game) {}
static void mod_random_spawn_tick(Game * game) {}
static void mod_random_spawn_deinitialize(Game * game) {}

void mod_random_spawn(GameModule * mod) {
  mod->initialize = mod_random_spawn_initialize;
  mod->tick = mod_random_spawn_tick;
  mod->update = mod_random_spawn_update;
  mod->deinitialize = mod_random_spawn_deinitialize;
}
