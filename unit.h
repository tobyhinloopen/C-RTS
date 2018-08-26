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

#define UNIT_MODE_FORCE_MOVE_TARGET_POSITION 1

typedef struct Unit Unit;

#include "factory.h"

struct Unit {
  Vector position;
  Vector target_position;
  float direction;
  float head_direction;
  float head_throttle;
  float angular_throttle;
  float throttle;
  float next_fire_interval;
  float health;
  int team_id;
  int mode;
  Unit * closest_friendly_unit;
  Unit * closest_enemy_unit;
  Factory * closest_friendly_factory;
  Factory * closest_enemy_factory;
};

void unit_initialize(Unit *);
void unit_update(Unit *, float delta);
int unit_is_firing(const Unit *);
int unit_is_dead(const Unit *);
float unit_health_percentage(const Unit *);

#endif
