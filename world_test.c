#include <assert.h>
#include <stdlib.h>
#include "world_test.h"
#include "world.h"
#include "unit.h"

World world;
int test_world_iterate_units_iterator_callback_called;

void test_world_unit_allocate_single();
void test_world_unit_allocate_multiple();
void test_world_unit_allocate_after_deallocate();
void test_world_unit_allocate_after_deallocate_once();
void test_world_unit_allocate_after_deallocate_many_times();
void allocate_and_deallocate_unit_once();
void assert_allocated_unit(WorldUnit *);
void test_world_iterate_units_iterator_callback(Unit * unit);

void test_world() {
  test_world_initialize();
  test_world_unit_allocate();
  test_world_unit_deallocate();
  test_world_unit_allocate_after_deallocate();
  test_world_update();
}

void test_world_initialize() {
  world_initialize(&world);
  assert(world.unit_count == 0);
  assert(world.unit_pool_size == 0);
  assert(world.time == 0.0f);
  world_deinitialize(&world);
}

void test_world_unit_allocate() {
  test_world_unit_allocate_single();
  test_world_unit_allocate_multiple();
}

void test_world_unit_allocate_single() {
  world_initialize(&world);
  WorldUnit * world_unit = world_unit_allocate(&world);
  assert_allocated_unit(world_unit);
  assert(world.unit_pool_size >= 1);
  assert(world.unit_count == 1);
  assert(&world.units[0] == world_unit);
  world_deinitialize(&world);
}

void test_world_unit_allocate_multiple() {
  world_initialize(&world);
  WorldUnit * a = world_unit_allocate(&world);
  assert_allocated_unit(a);
  WorldUnit * b = world_unit_allocate(&world);
  assert_allocated_unit(b);
  WorldUnit * c = world_unit_allocate(&world);
  assert_allocated_unit(c);
  assert(a != b);
  assert(b != c);
  assert(world.unit_pool_size >= 3);
  assert(world.unit_count == 3);
  world_deinitialize(&world);
}

void test_world_unit_deallocate() {
  world_initialize(&world);
  WorldUnit * unit_foo = world_unit_allocate(&world);
  unit_initialize(&unit_foo->unit);
  WorldUnit * unit_bar = world_unit_allocate(&world);
  unit_initialize(&unit_bar->unit);
  world_unit_deallocate(&world, unit_foo);
  assert(!unit_foo->alive);
  assert(world.unit_pool_size >= 1);
  assert(world.unit_count == 1);
  world_deinitialize(&world);
}

void test_world_unit_allocate_after_deallocate() {
  test_world_unit_allocate_after_deallocate_once();
  test_world_unit_allocate_after_deallocate_many_times();
}

void test_world_unit_allocate_after_deallocate_once() {
  world_initialize(&world);
  allocate_and_deallocate_unit_once();
  assert_allocated_unit(world_unit_allocate(&world));
  assert(world.unit_count == 1);
  world_deinitialize(&world);
}

void test_world_unit_allocate_after_deallocate_many_times() {
  const int allocate_deallocate_cycle_count = 1024;
  const int max_expected_pool_size = 512;
  world_initialize(&world);
  for(int i=0; i<allocate_deallocate_cycle_count; i++)
    allocate_and_deallocate_unit_once();
  assert_allocated_unit(world_unit_allocate(&world));
  assert(world.unit_count == 1);
  assert(world.unit_pool_size < max_expected_pool_size);
  world_deinitialize(&world);
}

void test_world_update() {
  const float delta = 0.6f;
  const float throttle = 0.8f;
  world_initialize(&world);
  WorldUnit * world_unit = world_unit_allocate(&world);
  unit_initialize(&world_unit->unit);
  world_unit->unit.throttle = throttle;
  assert(world_unit->unit.throttle == throttle);
  world_update(&world, delta);
  Unit unit;
  unit_initialize(&unit);
  unit.throttle = throttle;
  unit_update(&unit, delta);
  assert(unit.position.x == world_unit->unit.position.x);
  assert(unit.position.y == world_unit->unit.position.y);
  world_deinitialize(&world);
}

void test_world_iterate_units() {
  world_initialize(&world);
  test_world_iterate_units_iterator_callback_called = 0;
  world_unit_allocate(&world);
  world_unit_allocate(&world);
  world_iterate_units(&world, test_world_iterate_units_iterator_callback);
  assert(test_world_iterate_units_iterator_callback_called == 2);
  world_deinitialize(&world);
}

void allocate_and_deallocate_unit_once() {
  world_unit_deallocate(&world, world_unit_allocate(&world));
}

void test_world_iterate_units_iterator_callback(Unit * unit) {
  ++test_world_iterate_units_iterator_callback_called;
}

void assert_allocated_unit(WorldUnit * world_unit) {
  assert(world_unit != NULL);
  assert(world_unit->alive);
}
