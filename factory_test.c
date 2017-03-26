#include "factory_test.h"
#include "factory.h"
#include <assert.h>
#include <math.h>

void test_factory() {
  Factory factory;
  Unit unit;
  factory_initialize(&factory);
  assert(factory.position.x == 0);
  assert(factory.position.y == 0);
  assert(factory.direction == 0);
  assert(factory.team_id == 0);
  assert(factory.health == FACTORY_INITIAL_HEALTH);
  assert(factory.next_build_interval == INFINITY);
  assert(factory_health_percentage(&factory) == 1);
  assert(!factory_is_building(&factory));
  factory.position.x = 4;
  factory.position.y = 8;
  factory.team_id = 0xF00;
  factory_start_building(&factory);
  assert(factory_is_building(&factory));
  assert(!factory_try_build_unit(&factory, &unit));
  factory_update(&factory, FACTORY_BUILD_INTERVAL);
  assert(factory_try_build_unit(&factory, &unit));
  assert(unit.position.x == 4);
  assert(unit.position.y == 8);
  assert(unit.team_id == 0xF00);
  assert(!factory_try_build_unit(&factory, &unit));
  factory_stop_building(&factory);
  assert(!factory_is_building(&factory));
  factory.health = 10;
  factory_update(&factory, 1);
  assert(factory.health == 10 + FACTORY_HEALTH_REGENERATION);
  factory.health = FACTORY_INITIAL_HEALTH / 2;
  assert(factory_health_percentage(&factory) == 0.5);
  factory.health = 0;
  assert(factory_health_percentage(&factory) == 0);
  assert(factory_is_dead(&factory));
}
