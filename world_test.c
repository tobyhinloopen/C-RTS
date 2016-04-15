#include <assert.h>
#include <stdlib.h>
#include "world_test.h"
#include "world.h"
#include "unit.h"

World world;
int test_world_iterate_entities_iterator_callback_called;

void test_world_initialize();
void test_world_entity_allocate();
void test_world_entity_deallocate();
void test_world_iterate_entities();
void test_world_update();
void test_world_deinitialize();

void test_world_entity_allocate_single();
void test_world_entity_allocate_multiple();
void test_world_entity_allocate_after_deallocate();
void test_world_entity_allocate_after_deallocate_once();
void test_world_entity_allocate_after_deallocate_many_times();
void allocate_and_deallocate_entity_once();
void assert_allocated_entity(Entity *, int type);
void test_world_iterate_entities_iterator_callback(Entity *, void *);

void test_world() {
  // test_world_initialize();
  // test_world_entity_allocate();
  // test_world_entity_deallocate();
  // test_world_entity_allocate_after_deallocate();
  // test_world_update();
}

// void test_world_initialize() {
//   world_initialize(&world);
//   assert(world.entity_count == 0);
//   assert(world.entity_pool_size == 0);
//   assert(world.time == 0);
//   world_deinitialize(&world);
// }
//
// void test_world_entity_allocate() {
//   test_world_entity_allocate_single();
//   test_world_entity_allocate_multiple();
// }
//
// void test_world_entity_allocate_single() {
//   world_initialize(&world);
//   Entity * entity = world_entity_allocate(&world, UNIT);
//   assert_allocated_entity(entity, UNIT);
//   assert(world.entity_pool_size >= 1);
//   assert(world.entity_count == 1);
//   assert(&world.entities[0] == entity);
//   world_deinitialize(&world);
// }
//
// void test_world_entity_allocate_multiple() {
//   world_initialize(&world);
//   Entity * a = world_entity_allocate(&world, UNIT);
//   assert_allocated_entity(a, UNIT);
//   Entity * b = world_entity_allocate(&world, UNIT);
//   assert_allocated_entity(b, UNIT);
//   Entity * c = world_entity_allocate(&world, UNIT);
//   assert_allocated_entity(c, UNIT);
//   assert(a != b);
//   assert(b != c);
//   assert(world.entity_pool_size >= 3);
//   assert(world.entity_count == 3);
//   world_deinitialize(&world);
// }
//
// void test_world_entity_deallocate() {
//   world_initialize(&world);
//   Entity * entity_foo = world_entity_allocate(&world, UNIT);
//   unit_initialize(&entity_foo->unit);
//   Entity * entity_bar = world_entity_allocate(&world, UNIT);
//   unit_initialize(&entity_bar->unit);
//   world_entity_deallocate(&world, entity_foo);
//   assert(entity_foo->type == NONE);
//   assert(world.entity_pool_size >= 1);
//   assert(world.entity_count == 1);
//   world_deinitialize(&world);
// }
//
// void test_world_entity_allocate_after_deallocate() {
//   test_world_entity_allocate_after_deallocate_once();
//   test_world_entity_allocate_after_deallocate_many_times();
// }
//
// void test_world_entity_allocate_after_deallocate_once() {
//   world_initialize(&world);
//   allocate_and_deallocate_entity_once();
//   assert_allocated_entity(world_entity_allocate(&world, UNIT), UNIT);
//   assert(world.entity_count == 1);
//   world_deinitialize(&world);
// }
//
// void test_world_entity_allocate_after_deallocate_many_times() {
//   const int allocate_deallocate_cycle_count = 1024;
//   const int max_expected_pool_size = 512;
//   world_initialize(&world);
//   for(int i=0; i<allocate_deallocate_cycle_count; i++)
//     allocate_and_deallocate_entity_once();
//   assert_allocated_entity(world_entity_allocate(&world, UNIT), UNIT);
//   assert(world.entity_count == 1);
//   assert(world.entity_pool_size < max_expected_pool_size);
//   world_deinitialize(&world);
// }
//
// void test_world_update() {
//   const float delta = 0.6f;
//   const float throttle = 0.8f;
//   world_initialize(&world);
//   Entity * entity = world_entity_allocate(&world, UNIT);
//   unit_initialize(&entity->unit);
//   entity->unit.throttle = throttle;
//   assert(entity->unit.throttle == throttle);
//   world_update(&world, delta);
//   Unit unit;
//   unit_initialize(&unit);
//   unit.throttle = throttle;
//   unit_update(&unit, delta);
//   assert(unit.position.x == entity->unit.position.x);
//   assert(unit.position.y == entity->unit.position.y);
//   world_deinitialize(&world);
// }
//
// void test_world_iterate_entities() {
//   world_initialize(&world);
//   test_world_iterate_entities_iterator_callback_called = 0;
//   world_entity_allocate(&world, UNIT);
//   world_entity_allocate(&world, UNIT);
//   world_iterate_entities(&world, NULL, test_world_iterate_entities_iterator_callback);
//   assert(test_world_iterate_entities_iterator_callback_called == 2);
//   world_deinitialize(&world);
// }
//
// void allocate_and_deallocate_entity_once() {
//   world_entity_deallocate(&world, world_entity_allocate(&world, UNIT));
// }
//
// void test_world_iterate_entities_iterator_callback(Entity * entity, void * arg) {
//   ++test_world_iterate_entities_iterator_callback_called;
// }
//
// void assert_allocated_entity(Entity * entity, int type) {
//   assert(entity != NULL);
//   assert(entity->type == type);
// }
