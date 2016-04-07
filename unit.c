#include "unit.h"
#include "vector.h"
#include "pi.h"
#include <math.h>

const float UNIT_PIXELS_PER_SECOND = 100;
const float UNIT_RADIANS_PER_SECOND = PI;
const float UNIT_HEAD_RADIANS_PER_SECOND = PI;

void unit_update_movement(Unit *, float delta);
void unit_update_straight_movement(Unit *, float delta);
void unit_update_angular_movement(Unit *, float delta);
void unit_update_head_direction(Unit *, float delta);

void unit_initialize(Unit * unit) {
  vector_initialize(&unit->position);
  unit->direction = 0;
  unit->angular_throttle = 0;
  unit->throttle = 0;
  unit->head_direction = 0;
  unit->head_throttle = 0;
  unit->team_id = 0;
}

void unit_update(Unit * unit, float delta) {
  if(unit->throttle > 0 && unit->angular_throttle == 0)
    unit_update_straight_movement(unit, delta);
  else if(unit->angular_throttle != 0)
    unit_update_angular_movement(unit, delta);
  if(unit->head_throttle != 0)
    unit_update_head_direction(unit, delta);
}

void unit_update_straight_movement(Unit * unit, float delta) {
  float forward_movement = unit->throttle * UNIT_PIXELS_PER_SECOND * delta;
  unit->position.x -= forward_movement * sinf(unit->direction);
  unit->position.y += forward_movement * cosf(unit->direction);
}

void unit_update_angular_movement(Unit * unit, float delta) {
  float angular_motion = unit->angular_throttle * UNIT_RADIANS_PER_SECOND;
  float movement_radius = unit->throttle * UNIT_PIXELS_PER_SECOND / angular_motion;
  float angular_movement = angular_motion * delta;

  Vector movement = {
    movement_radius * cosf(angular_movement) - movement_radius,
    movement_radius * sinf(angular_movement)
  };

  vector_rotate(&movement, unit->direction);
  vector_add(&unit->position, movement);

  unit->direction += angular_movement;
}

void unit_update_head_direction(Unit * unit, float delta) {
  unit->head_direction += unit->head_throttle * UNIT_RADIANS_PER_SECOND * delta;
}
