#include "factory.h"
#include <math.h>

void factory_initialize(Factory * factory) {
  vector_initialize(&factory->position);
  factory->direction = 0;
  factory->team_id = 0;
  factory->health = FACTORY_INITIAL_HEALTH;
  factory->next_build_interval = INFINITY;
}

int factory_is_dead(Factory * factory) {
  return factory->health <= 0;
}

int factory_is_building(Factory * factory) {
  return factory->next_build_interval != INFINITY;
}

void factory_start_building(Factory * factory) {
  factory->next_build_interval = FACTORY_BUILD_INTERVAL;
}

void factory_stop_building(Factory * factory) {
  factory->next_build_interval = INFINITY;
}

static void factory_update_health_regeneration(Factory * factory, float delta) {
  if (!factory_is_building(factory) && !factory_is_dead(factory) && factory->health < FACTORY_INITIAL_HEALTH) {
    factory->health += FACTORY_HEALTH_REGENERATION * delta;
    if (factory->health > FACTORY_INITIAL_HEALTH) {
      factory->health = FACTORY_INITIAL_HEALTH;
    }
  }
}

void factory_update(Factory * factory, float delta) {
  factory_update_health_regeneration(factory, delta);
  factory->next_build_interval -= delta;
}

int factory_try_build_unit(Factory * factory, Unit * unit) {
  if (factory_is_dead(factory) || factory->next_build_interval > 0) {
    return 0;
  } else {
    float unit_update_delta = -factory->next_build_interval;
    factory->next_build_interval += FACTORY_BUILD_INTERVAL;
    unit_initialize(unit);
    unit->position = factory->position;
    unit->direction = factory->direction;
    unit->throttle = 1;
    unit->team_id = factory->team_id;
    unit_update(unit, unit_update_delta);
    return 1;
  }
}

float factory_health_percentage(Factory * factory) {
  return factory->health <= 0 ? 0 : factory->health / FACTORY_INITIAL_HEALTH;
}

float factory_build_percentage(Factory * factory) {
  return factory->next_build_interval <= 0 ? 0 : 1 - factory->next_build_interval / FACTORY_BUILD_INTERVAL;
}
