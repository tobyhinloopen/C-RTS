#include "unit.h"
#include "vector.h"
#include "pi.h"
#include <math.h>

const float UNIT_PIXELS_PER_SECOND = 100;
const float UNIT_RADIANS_PER_SECOND = HALF_PI;
const float UNIT_HEAD_RADIANS_PER_SECOND = PI2;
const float UNIT_FIRE_INTERVAL = 0.5f;
const float UNIT_INITIAL_HEALTH = 400;
const float UNIT_HEALTH_REGENERATION = 20;

void unit_initialize(Unit * unit) {
  vector_initialize(&unit->position);
  unit->direction = 0;
  unit->angular_throttle = 0;
  unit->throttle = 0;
  unit->head_direction = 0;
  unit->head_throttle = 0;
  unit->next_fire_interval = INFINITY;
  unit->health = UNIT_INITIAL_HEALTH;
  unit->team_id = 0;
}

static void unit_update_straight_movement(Unit * unit, float delta) {
  float forward_movement = unit->throttle * UNIT_PIXELS_PER_SECOND * delta;
  unit->position.x -= forward_movement * sinf(unit->direction);
  unit->position.y += forward_movement * cosf(unit->direction);
}

static void unit_update_angular_movement(Unit * unit, float delta) {
  float angular_motion = unit->angular_throttle * UNIT_RADIANS_PER_SECOND;
  float movement_radius = unit->throttle * UNIT_PIXELS_PER_SECOND / angular_motion;
  float angular_movement = angular_motion * delta;

  Vector movement = {
    movement_radius * sinf(angular_movement),
    movement_radius * cosf(angular_movement) - movement_radius
  };

  vector_rotate(&movement, unit->direction);
  vector_add(&unit->position, movement);

  unit->direction += angular_movement;
}

static void unit_update_head_direction(Unit * unit, float delta) {
  unit->head_direction += unit->head_throttle * UNIT_HEAD_RADIANS_PER_SECOND * delta;
}

static void unit_update_health_regeneration(Unit * unit, float delta) {
  unit->health += UNIT_HEALTH_REGENERATION * delta;
  if(unit->health > UNIT_INITIAL_HEALTH)
    unit->health = UNIT_INITIAL_HEALTH;
}

void unit_update(Unit * unit, float delta) {
  if(unit->throttle > 0 && unit->angular_throttle == 0)
    unit_update_straight_movement(unit, delta);
  else if(unit->angular_throttle != 0)
    unit_update_angular_movement(unit, delta);
  if(unit->head_throttle != 0)
    unit_update_head_direction(unit, delta);
  if(unit->throttle <= 1.0f && unit->health > 0.0f && unit->health < UNIT_INITIAL_HEALTH)
    unit_update_health_regeneration(unit, delta);
  unit->next_fire_interval -= delta;
}

int unit_is_firing(Unit * unit) {
  return isfinite(unit->next_fire_interval);
}

int unit_is_dead(Unit * unit) {
  return unit->health <= 0;
}

float unit_health_percentage(Unit * unit) {
  return unit->health <= 0 ? 0 : unit->health / UNIT_INITIAL_HEALTH;
}
