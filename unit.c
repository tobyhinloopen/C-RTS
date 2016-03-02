#include "unit.h"
#include "vector.h"

void unit_update_movement(Unit *unit, float delta);

void unit_initialize(Unit *unit) {
  vector_initialize(&unit->position);
  unit->direction = 0.0f;
  unit->throttle = 0.0f;
}

void unit_update(Unit *unit, float delta) {
  if(unit->throttle > 0.0f)
    unit_update_movement(unit, delta);
}

void unit_update_movement(Unit *unit, float delta) {
  Vector movement = (Vector) { 0, unit->throttle * delta };
  vector_rotate(&movement, unit->direction);
  vector_add(&unit->position, movement);
}
