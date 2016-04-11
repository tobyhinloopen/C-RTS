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

static void unit_behavior_set_closer_unit(Unit * other_unit, void * current_result_ptr) {
  UnitPairDistanceResult * current_result = (UnitPairDistanceResult*)current_result_ptr;
  Unit * my_unit = current_result->my_unit;
  if(other_unit->team_id != my_unit->team_id) {
    float distance = vector_distance(other_unit->position, my_unit->position);
    if(current_result->closest_unit == 0 || distance < current_result->distance) {
      current_result->distance = distance;
      current_result->closest_unit = other_unit;
    }
  }
}

Unit * unit_behavior_find_closest_enemy_unit(Unit * unit, World * world) {
  UnitPairDistanceResult closest_enemy_unit_result = { 0, unit, 0 };
  world_iterate_units(world, &closest_enemy_unit_result, unit_behavior_set_closer_unit);
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
