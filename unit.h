#ifndef UNIT_H
#define UNIT_H

#include "vector.h"

extern const float UNIT_PIXELS_PER_SECOND;
extern const float UNIT_RADIANS_PER_SECOND;
extern const float UNIT_HEAD_RADIANS_PER_SECOND;
extern const float UNIT_FIRE_INTERVAL;
extern const float UNIT_INITIAL_HEALTH;
extern const float UNIT_HEALTH_REGENERATION;

typedef struct {
  Vector position;
  float direction;
  float head_direction;
  float head_throttle;
  float angular_throttle;
  float throttle;
  float next_fire_interval;
  float health;
  int team_id;
} Unit;

void unit_initialize(Unit *);
void unit_update(Unit *, float delta);
int unit_is_firing(Unit *);
int unit_is_dead(Unit *);
float unit_health_percentage(Unit *);

#endif
