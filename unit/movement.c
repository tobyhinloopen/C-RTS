#include "movement.h"
#include <math.h>
#include "../pi.h"

void unit_movement_set_target_position(Unit * unit, Vector target_position, float min_distance) {
  if(vector_distance(unit->position, target_position) < min_distance) {
    unit->throttle = 0;
  } else {
    unit->throttle = 1;
    Vector target_movement = target_position;
    vector_subtract(&target_movement, unit->position);
    float angular_difference = remainderf(
      atan2f(-target_movement.x, target_movement.y) - unit->direction, PI2);
    unit->angular_throttle = angular_difference > 0 ? 1 : -1;
  }
}
