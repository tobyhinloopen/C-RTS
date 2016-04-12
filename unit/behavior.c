#include "behavior.h"
#include <math.h>
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
  if(other_unit->team_id != my_unit->team_id) {
    float distance = vector_distance(other_unit->position, my_unit->position);
    if(result->closest_unit == 0 || distance < result->distance) {
      result->distance = distance;
      result->closest_unit = other_unit;
    }
  }
}

static void unit_behavior_find_closest_enemy_unit_callback(Entity * entity, void * current_result_ptr) {
  if(entity->type == UNIT)
    unit_behavior_set_closer_unit(&entity->unit, (UnitPairDistanceResult*)current_result_ptr);
}

Unit * unit_behavior_find_closest_enemy_unit(Unit * unit, World * world) {
  UnitPairDistanceResult closest_enemy_unit_result = { 0, unit, 0 };
  world_iterate_entities(world, &closest_enemy_unit_result,
    unit_behavior_find_closest_enemy_unit_callback);
  return closest_enemy_unit_result.closest_unit;
}

void unit_behavior_stop(Unit * unit) {
  unit->throttle = 0;
  unit->angular_throttle = 0;
}

void unit_behavior_set_target_position(Unit * unit, Vector target_position, float min_distance) {
  if(vector_distance(unit->position, target_position) < min_distance) {
    unit_behavior_stop(unit);
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
