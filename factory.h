#ifndef FACTORY_H
#define FACTORY_H

#define FACTORY_INITIAL_HEALTH 8000
#define FACTORY_HEALTH_REGENERATION 200
#define FACTORY_BUILD_INTERVAL 0.5

#include "vector.h"

typedef struct Factory Factory;

#include "unit.h"

struct Factory {
  Vector position;
  float direction;
  int team_id;
  float health;
  float next_build_interval;
};

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
