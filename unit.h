#ifndef UNIT_H
#define UNIT_H

#include "vector.h"

extern const float UNIT_PIXELS_PER_SECOND;

typedef struct {
  Vector position;
  float direction;
  float throttle;
} Unit;

void unit_initialize(Unit *unit);
void unit_update(Unit *unit, float delta);

#endif
