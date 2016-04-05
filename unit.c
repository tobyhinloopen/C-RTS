#include "unit.h"
#include "vector.h"
#include "pi.h"

const float UNIT_PIXELS_PER_SECOND = 100.0f;
const float UNIT_RADIANS_PER_SECOND = 3.1415927f;

void unit_update_movement(Unit *unit, float delta);

void unit_initialize(Unit *unit) {
  vector_initialize(&unit->position);
  unit->direction = 0.0f;
  unit->angular_throttle = 0.0f;
  unit->throttle = 0.0f;
}

void unit_update(Unit *unit, float delta) {
  if(unit->throttle > 0.0f)
    unit_update_movement(unit, delta);
}

void unit_update_movement(Unit *unit, float delta) {
  Vector movement = (Vector) { 0, unit->throttle * delta * UNIT_PIXELS_PER_SECOND };
  float angular_motion = unit->angular_throttle * UNIT_RADIANS_PER_SECOND * delta;
  vector_rotate(&movement, unit->direction + angular_motion/2);
  vector_add(&unit->position, movement);
  unit->direction += angular_motion;
}
