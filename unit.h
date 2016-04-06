#ifndef UNIT_H
#define UNIT_H

#include "vector.h"

extern const float UNIT_PIXELS_PER_SECOND;
extern const float UNIT_RADIANS_PER_SECOND;
extern const float UNIT_HEAD_RADIANS_PER_SECOND;

typedef struct {
  Vector position;
  float direction; // Direction in radians
  float head_direction;
  float head_throttle;
  float angular_throttle;
  float throttle;
  int team_id;
} Unit;

void unit_initialize(Unit *unit);
void unit_update(Unit *unit, float delta);

#endif
