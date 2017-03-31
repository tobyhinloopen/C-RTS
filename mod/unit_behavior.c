#include "unit_behavior.h"
#include "../unit/behavior.h"
#include "../config.h"

#ifdef CONFIG_GRID_ENABLED
#include "../grid.h"
#include <math.h>

#ifdef CONFIG_GRID_CHECK
#include <assert.h>
#include <stdio.h>
#endif

#define GRID_CHECK

typedef struct {
  Unit * my_unit;
  Factory * factory;
  float factory_distance;
  Unit * unit;
  float unit_distance;
} ClosestFriendlyResult;

static void update_closest_friendly_result(void * entity_ptr, void * result_ptr) {
  Entity * entity = (Entity *)entity_ptr;
  ClosestFriendlyResult * result = (ClosestFriendlyResult *)result_ptr;

  if (entity->type == UNIT) {
    if (&entity->unit != result->my_unit && entity->unit.team_id == result->my_unit->team_id) {
      float distance = vector_distance(result->my_unit->position, entity->unit.position);
      if (distance < result->unit_distance) {
        result->unit = &entity->unit;
        result->unit_distance = distance;
      }
    }
  } else if(entity->type == FACTORY) {
    if (entity->factory.team_id == result->my_unit->team_id) {
      float distance = vector_distance(result->my_unit->position, entity->factory.position);
      if (distance < result->factory_distance) {
        result->factory = &entity->factory;
        result->factory_distance = distance;
      }
    }
  }
}
#endif

static void update_unit_behavior(Unit * unit, Game * game) {
  World * world = &game->world;
  Unit * closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);

#ifdef CONFIG_GRID_ENABLED
  ClosestFriendlyResult result = {unit, NULL, 32.0f, NULL, 32.0f};

  unsigned int x = 47.5f + unit->position.x / 64;
  unsigned int y = 47.5f + unit->position.y / 64;
  grid_iterate_items(&game->grid, (GridXY){ x, y }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x, y + 1 }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x + 1, y }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x + 1, y + 1 }, &result, update_closest_friendly_result);

  Unit * closest_friendly_unit = result.unit;
  Factory * closest_friendly_factory = result.factory;

#ifdef CONFIG_GRID_CHECK
  Unit * check_closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);
  if (check_closest_friendly_unit != closest_friendly_unit) {
    assert(0);
  }
  Factory * check_closest_friendly_factory = unit_behavior_find_closest_friendly_factory(unit, world, 32.0f);
  if (check_closest_friendly_factory != closest_friendly_factory) {
    assert(0);
  }
#endif

#else
  Unit * closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);
  Factory * closest_friendly_factory = unit_behavior_find_closest_friendly_factory(unit, world, 32.0f);
#endif

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

static void update_entity_unit_behavior(Entity * entity, void * game_ptr) {
  if(entity->type == UNIT) {
    update_unit_behavior(&entity->unit, (Game *)game_ptr);
  }
}

static void mod_unit_behavior_update(Game * game, unsigned int delta) {
  world_iterate_entities(&game->world, game, update_entity_unit_behavior);
}

void mod_unit_behavior(GameModule * mod) {
  mod->update = mod_unit_behavior_update;
}
