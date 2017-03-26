#ifndef FACTORY_H
#define FACTORY_H

#include "vector.h"
#include "unit.h"

extern const float FACTORY_INITIAL_HEALTH;
extern const float FACTORY_HEALTH_REGENERATION;
extern const float FACTORY_BUILD_INTERVAL;

typedef struct {
  Vector position;
  float direction;
  int team_id;
  float health;
  float next_build_interval;
} Factory;

void factory_initialize(Factory *);
int factory_is_dead(Factory *);
int factory_is_building(Factory *);
void factory_start_building(Factory *);
void factory_stop_building(Factory *);
void factory_update(Factory *, float);
int factory_try_build_unit(Factory *, Unit *);
float factory_health_percentage(Factory *);
float factory_build_percentage(Factory *);

#endif
