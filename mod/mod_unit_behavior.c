#include "mod_unit_behavior.h"
#include "../unit/behavior.h"
#include <float.h>

#define OVERDRIVE_DISTANCE 480
#define FLEE_DISTANCE 960
#define PREFER_ENEMY_FACTORY_DISTANCE 480
#define FRIENDLY_UNIT_DISTANCE_SQ (32 * 32)
#define FRIENDLY_FACTORY_DISTANCE_SQ (32 * 32)

static Vector get_closest_point_inside(Map * map, Vector pos, float distance) {
  const float max_x = map->size.x - distance;
  if (pos.x < distance)
    pos.x = distance;
  else if (pos.x > max_x)
    pos.x = max_x;

  const float max_y = map->size.y - distance;
  if (pos.y < distance)
    pos.y = distance;
  else if (pos.y > max_y)
    pos.y = max_y;
  return pos;
}

static void update_unit_behavior(Unit * unit, Game * game) {
  Vector pos = unit->position;

  Map * map = &game->map;
  Unit * closest_enemy_unit = unit->closest_enemy_unit;
  Unit * closest_friendly_unit = unit->closest_friendly_unit;
  Factory * closest_friendly_factory = unit->closest_friendly_factory;
  Factory * closest_enemy_factory = unit->closest_enemy_factory;

  float enemy_unit_distance = closest_enemy_unit == NULL ? FLT_MAX : vector_distance(pos, closest_enemy_unit->position);
  float enemy_factory_distance = closest_enemy_factory == NULL ? FLT_MAX : vector_distance(pos, closest_enemy_factory->position);

  Vector enemy_target_position;
  if (closest_enemy_unit != NULL && closest_enemy_factory != NULL) {
    enemy_target_position = enemy_unit_distance - enemy_factory_distance < PREFER_ENEMY_FACTORY_DISTANCE ? closest_enemy_unit->position : closest_enemy_factory->position;
  } else if (closest_enemy_unit != NULL)
    enemy_target_position = closest_enemy_unit->position;
  else if (closest_enemy_factory != NULL)
    enemy_target_position = closest_enemy_factory->position;

  float unit_health = unit_health_percentage(unit);

  if (pos.x < 0 || pos.x > map->size.x || pos.y < 0 || pos.y > map->size.y)
    unit_behavior_set_target_position(unit, get_closest_point_inside(map, pos, 64.0f), 32.0f);
  else if (closest_friendly_factory != NULL && vector_sq_distance(pos, closest_friendly_factory->position) <= FRIENDLY_FACTORY_DISTANCE_SQ)
    unit_behavior_move_away_from(unit, closest_friendly_factory->position);
  else if (closest_friendly_unit != NULL && vector_sq_distance(pos, closest_friendly_unit->position) <= FRIENDLY_UNIT_DISTANCE_SQ)
    unit_behavior_move_away_from(unit, closest_friendly_unit->position);
  else if (closest_enemy_unit != NULL && unit_health < 0.5f && enemy_unit_distance < FLEE_DISTANCE)
    unit_behavior_evasive_flee_from(unit, closest_enemy_unit->position);
  else if (closest_enemy_unit != NULL || closest_enemy_factory != NULL)
    unit_behavior_set_target_position(unit, enemy_target_position, 120.0f);
  else
    unit_behavior_movement_stop(unit);

  if(closest_enemy_unit != NULL || closest_enemy_factory != NULL)
    unit_behavior_head_engage_position(unit, enemy_target_position);
  else if(unit_health < 0.2f && enemy_unit_distance < OVERDRIVE_DISTANCE)
    unit_behavior_overdrive(unit);
  else
    unit_behavior_head_stop(unit);
}

static void update_entity_unit_behavior(Entity * entity, void * game_ptr) {
  if(entity->type == UNIT) {
    update_unit_behavior(&entity->unit, (Game *)game_ptr);
  }
}

static void mod_unit_behavior_update(Game * game, unsigned int delta) {
  world_iterate_entities_of_type(&game->world, UNIT, game, update_entity_unit_behavior);
}

void mod_unit_behavior(GameModule * mod) {
  mod->update = mod_unit_behavior_update;
}
