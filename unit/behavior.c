#include "behavior.h"
#include <math.h>
#include <stdlib.h>
#include "../pi.h"

static void unit_behavior_target_head_direction(Unit * unit, float target_head_direction) {
  unit->head_throttle = remainderf(target_head_direction - unit->head_direction, PI2) > 0 ? 1 : -1;
}

void unit_behavior_look_at(Unit * unit, Vector target_position) {
  unit_behavior_target_head_direction(unit,
    vector_angle_between(unit->position, target_position) - unit->direction);
}

void unit_behavior_look_forward(Unit * unit) {
  unit_behavior_target_head_direction(unit, 0);
}

typedef struct {
  float distance;
  Unit * my_unit;
  Unit * closest_unit;
} UnitPairDistanceResult;

static void unit_behavior_set_closer_unit(Unit * other_unit, UnitPairDistanceResult * result) {
  Unit * my_unit = result->my_unit;
  float distance = vector_distance(other_unit->position, my_unit->position);
  if(result->closest_unit == 0 || distance < result->distance) {
    result->distance = distance;
    result->closest_unit = other_unit;
  }
}

static void unit_behavior_find_closest_enemy_unit_callback(Entity * entity, void * current_result_ptr) {
  UnitPairDistanceResult * result = (UnitPairDistanceResult*)current_result_ptr;
  if(entity->type == UNIT && entity->unit.team_id != result->my_unit->team_id)
    unit_behavior_set_closer_unit(&entity->unit, result);
}

Unit * unit_behavior_find_closest_enemy_unit(Unit * unit, World * world) {
  UnitPairDistanceResult closest_enemy_unit_result = { 0, unit, 0 };
  world_iterate_entities(world, &closest_enemy_unit_result,
    unit_behavior_find_closest_enemy_unit_callback);
  return closest_enemy_unit_result.closest_unit;
}

static void unit_behavior_find_closest_friendly_unit_callback(Entity * entity, void * current_result_ptr) {
  UnitPairDistanceResult * result = (UnitPairDistanceResult*)current_result_ptr;
  if(entity->type == UNIT && &entity->unit != result->my_unit && entity->unit.team_id == result->my_unit->team_id)
    unit_behavior_set_closer_unit(&entity->unit, result);
}

Unit * unit_behavior_find_closest_friendly_unit(Unit * unit, World * world, float max_distance) {
  UnitPairDistanceResult closest_friendly_unit_result = { 0, unit, 0 };
  world_iterate_entities(world, &closest_friendly_unit_result,
    unit_behavior_find_closest_friendly_unit_callback);
  if(closest_friendly_unit_result.distance <= max_distance)
    return closest_friendly_unit_result.closest_unit;
  else
    return NULL;
}

void unit_behavior_movement_stop(Unit * unit) {
  unit->throttle = 0;
  unit->angular_throttle = 0;
}

void unit_behavior_head_stop(Unit * unit) {
  unit_behavior_look_forward(unit);
  unit_behavior_hold_fire(unit);
}

void unit_behavior_move_away_from(Unit * unit, Vector position) {
  vector_subtract(&position, unit->position);
  vector_rotate(&position, PI);
  vector_add(&position, unit->position);
  unit_behavior_set_target_position(unit, position, 0.0f);
}

void unit_behavior_evasive_flee_from(Unit * unit, Vector position) {
  vector_subtract(&position, unit->position);
  vector_rotate(&position, HALF_PI);
  vector_multiply_scalar(&position, 4.0f);
  vector_add(&position, unit->position);
  unit_behavior_set_target_position(unit, position, 0.0f);
}

void unit_behavior_overdrive(Unit * unit) {
  unit_behavior_look_forward(unit);
  unit_behavior_hold_fire(unit);
  unit->throttle = 1.3f;
}

/**
 * Get the angular distance between a unit's absolute head position and the angle between the
 * unit's position and a target position. The distance is returned as a positive number in radians.
 */
static float unit_behavior_look_at_distance(Unit * unit, Vector position) {
  float target_angle = vector_angle_between(unit->position, position);
  float angular_diff = remainderf(target_angle - unit->direction - unit->head_direction, PI2);
  return angular_diff < 0 ? -angular_diff : angular_diff;
}

/**
 * Order the unit "head" to look at a target position and open fire when looking at the target's
 * position.
 */
void unit_behavior_head_engage_position(Unit * unit, Vector target_position) {
  unit_behavior_look_at(unit, target_position);
  if(unit_behavior_look_at_distance(unit, target_position) < PI2 * 0.05f)
    unit_behavior_open_fire(unit);
  else
    unit_behavior_hold_fire(unit);
}

void unit_behavior_set_target_position(Unit * unit, Vector target_position, float min_distance) {
  if(vector_distance(unit->position, target_position) < min_distance) {
    unit_behavior_movement_stop(unit);
  } else {
    unit->throttle = 1;
    unit->angular_throttle = remainderf(
      vector_angle_between(unit->position, target_position) - unit->direction, PI2) > 0 ? 1 : -1;
  }
}

void unit_behavior_open_fire(Unit * unit) {
  if(!unit_is_firing(unit))
    unit->next_fire_interval = UNIT_FIRE_INTERVAL;
}

void unit_behavior_hold_fire(Unit * unit) {
  if(unit_is_firing(unit))
    unit->next_fire_interval = INFINITY;
}
