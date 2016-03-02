#ifndef UNIT_H
#define UNIT_H

#include "vector.h"

typedef struct {
  Vector position;
  float direction;
  float throttle;
} Unit;

void unit_initialize(Unit *unit);
void unit_update(Unit *unit, float delta);

#endif
