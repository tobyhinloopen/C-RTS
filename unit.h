#ifndef UNIT_H
#define UNIT_H

#include "vector.h"
#include "pi.h"

#define UNIT_PIXELS_PER_SECOND 100
#define UNIT_RADIANS_PER_SECOND HALF_PI
#define UNIT_HEAD_RADIANS_PER_SECOND PI2
#define UNIT_FIRE_INTERVAL 0.5
#define UNIT_INITIAL_HEALTH 400
#define UNIT_HEALTH_REGENERATION 20

typedef struct Unit Unit;

#include "factory.h"

struct Unit {
  Vector position;
  float direction;
  float head_direction;
  float head_throttle;
  float angular_throttle;
  float throttle;
  float next_fire_interval;
  float health;
  int team_id;
  Unit * closest_friendly_unit;
  Unit * closest_enemy_unit;
  Factory * closest_friendly_factory;
  Factory * closest_enemy_factory;
};

void unit_initialize(Unit *);
void unit_update(Unit *, float delta);
int unit_is_firing(Unit *);
int unit_is_dead(Unit *);
float unit_health_percentage(Unit *);

#endif
