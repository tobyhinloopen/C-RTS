#include "mod_unit_behavior.h"
#include "../unit/behavior.h"
#include "../config.h"
#include <math.h>

#ifdef CONFIG_GRID_ENABLED
#define ANY_GRID_ENABLED
#endif
#ifdef CONFIG_SCALABLE_GRID_ENABLED
#define ANY_GRID_ENABLED
#endif

#ifdef ANY_GRID_ENABLED
#include "../grid.h"
#include <stdio.h>

typedef struct {
  Unit * my_unit;
  Factory * factory;
  float factory_distance;
  Unit * unit;
  float unit_distance;
} ClosestFriendlyResult;


#ifdef CONFIG_GRID_CHECK
#include <assert.h>
#endif

static void update_closest_friendly_result(
void * entity_ptr,
#ifdef CONFIG_SCALABLE_GRID_ENABLED
float distance,
#endif
void * result_ptr
) {
  Entity * entity = (Entity *)entity_ptr;
  ClosestFriendlyResult * result = (ClosestFriendlyResult *)result_ptr;

  if (entity->type == UNIT) {
    if (&entity->unit != result->my_unit && entity->unit.team_id == result->my_unit->team_id) {
#ifndef CONFIG_SCALABLE_GRID_ENABLED
      float distance = vector_distance(result->my_unit->position, entity->unit.position);
#endif
      if (distance < result->unit_distance) {
        result->unit = &entity->unit;
        result->unit_distance = distance;
      }
    }
  } else if(entity->type == FACTORY) {
    if (entity->factory.team_id == result->my_unit->team_id) {
#ifndef CONFIG_SCALABLE_GRID_ENABLED
      float distance = vector_distance(result->my_unit->position, entity->factory.position);
#endif
      if (distance < result->factory_distance) {
        result->factory = &entity->factory;
        result->factory_distance = distance;
      }
    }
  }
}
#endif

#ifndef CONFIG_KDTREE_ENEMY_SEARCH
#ifdef CONFIG_SCALABLE_GRID_ENABLED
typedef struct {
  int team_id;
  float distance;
  Unit * unit;
} ClosestEnemyUnitResult;

static void update_enemy_unit_result(void * entity_ptr, float distance, void * result_ptr) {
  Entity * entity = (Entity *)entity_ptr;
  ClosestEnemyUnitResult * result = (ClosestEnemyUnitResult *)result_ptr;
  Unit * unit = &entity->unit;
  if (entity->type == UNIT && unit->team_id != result->team_id && distance < result->distance) {
    result->distance = distance;
    result->unit = unit;
  }
}
#endif
#endif

#ifdef CONFIG_KDTREE_ENEMY_SEARCH
#include "../kdtree.h"

Unit * kdtree_search_closest_enemy_unit(Game * game, Vector position, int team_id) {
  Unit * closest_enemy_unit = NULL;
  float closest_enemy_unit_distance = INFINITY;
  for (int i = 0; i < TEAM_COUNT; i++) {
    if (i != team_id) {
      KDTreeFindResult result = kdtree_find_distance(&game->kdtree[i], position);
      if (result.ref != NULL && result.distance < closest_enemy_unit_distance) {
        closest_enemy_unit = (Unit *)result.ref;
        closest_enemy_unit_distance = result.distance;
      }
    }
  }
  return closest_enemy_unit;
}
#endif

#ifdef CONFIG_KDTREE_ENEMY_SEARCH
#ifdef CONFIG_KDTREE_ENEMY_SEARCH_CHECK
#include <assert.h>

void print_unit_debug(void * other_unit_ptr, void * own_unit_ptr) {
  Unit * other_unit = (Unit *)other_unit_ptr;
  Unit * own_unit = (Unit *)own_unit_ptr;
  printf("d: %4.1f", vector_distance(other_unit->position, own_unit->position));
}

#endif
#endif

static void update_unit_behavior(Unit * unit, Game * game) {
#ifdef CONFIG_KDTREE_ENEMY_SEARCH
  Unit * closest_enemy_unit = kdtree_search_closest_enemy_unit(game, unit->position, unit->team_id);
#ifdef CONFIG_KDTREE_ENEMY_SEARCH_CHECK
  World * world = &game->world;
  Unit * check_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
  if (check_enemy_unit != closest_enemy_unit) {
    float actual_distance = vector_distance(closest_enemy_unit->position, unit->position);
    float expected_distance = vector_distance(check_enemy_unit->position, unit->position);
    printf("Found: %p (%f, %i), Expected: %p (%f, %i)\n",
      closest_enemy_unit, actual_distance, closest_enemy_unit->team_id, check_enemy_unit, expected_distance, check_enemy_unit->team_id);
    printf("Found Team ID: %i; Own Unit Position: %4.1f,%4.1f\n", closest_enemy_unit->team_id, unit->position.x, unit->position.y);
    kdtree_debug_print(&game->kdtree[closest_enemy_unit->team_id], unit, print_unit_debug);
    if (closest_enemy_unit->team_id != check_enemy_unit->team_id) {
      printf("Expected TEAM ID: %i\n", check_enemy_unit->team_id);
      kdtree_debug_print(&game->kdtree[check_enemy_unit->team_id], unit, print_unit_debug);
    }

    kdtree_find_distance(&game->kdtree[check_enemy_unit->team_id], unit->position);
    assert(0);
  }
#endif
#else
  World * world = &game->world;
#ifdef CONFIG_SCALABLE_GRID_QUICK_SHORT_RANGE_ENEMY_SEARCH
  ClosestEnemyUnitResult enemy_unit_result = {unit->team_id, FP_INFINITE, NULL};
  scalable_grid_iterate_items(&game->scalable_grid, unit->position, CONFIG_SCALABLE_GRID_QUICK_SHORT_RANGE_ENEMY_SEARCH, &enemy_unit_result, update_enemy_unit_result);
  Unit * closest_enemy_unit = enemy_unit_result.unit;
#else
  Unit * closest_enemy_unit = NULL;
#endif
  if (closest_enemy_unit == NULL)
    closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
#endif

#ifdef ANY_GRID_ENABLED
  ClosestFriendlyResult result = {unit, NULL, 32.0f, NULL, 32.0f};


#ifdef CONFIG_SCALABLE_GRID_ENABLED
  scalable_grid_iterate_items(&game->scalable_grid, unit->position, 32, &result, update_closest_friendly_result);
#else
  unsigned int x = 47.5f + unit->position.x / 64;
  unsigned int y = 47.5f + unit->position.y / 64;
  grid_iterate_items(&game->grid, (GridXY){ x, y }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x, y + 1 }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x + 1, y }, &result, update_closest_friendly_result);
  grid_iterate_items(&game->grid, (GridXY){ x + 1, y + 1 }, &result, update_closest_friendly_result);
#endif

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
