#include <assert.h>
#include "unit_test.h"
#include "unit.h"
#include "pi.h"

Unit unit;

void test_unit_without_throttle_doesnt_move();
void test_unit_without_delta_doesnt_move();
void test_unit_with_throttle_and_delta_does_move();
void test_unit_moves_in_direction();
void assert_position(float x, float y);

void test_unit() {
  test_unit_initialize();
  test_unit_update();
}

void test_unit_initialize() {
  unit_initialize(&unit);
  assert_position(0.0f, 0.0f);
  assert(unit.direction == 0.0f);
  assert(unit.throttle == 0.0f);
}

void test_unit_update() {
  test_unit_without_throttle_doesnt_move();
  test_unit_without_delta_doesnt_move();
  test_unit_with_throttle_and_delta_does_move();
}

void test_unit_without_throttle_doesnt_move() {
  unit_initialize(&unit);
  unit.throttle = 0.0f;
  unit_update(&unit, 1.0f);
  assert_position(0.0f, 0.0f);
}

void test_unit_without_delta_doesnt_move() {
  unit_initialize(&unit);
  unit.throttle = 1.0f;
  unit_update(&unit, 0.0f);
  assert_position(0.0f, 0.0f);
}

void test_unit_with_throttle_and_delta_does_move() {
  unit_initialize(&unit);
  unit.throttle = 1.0f;
  unit_update(&unit, 1.0f);
  assert_position(0.0f, 1.0f * UNIT_PIXELS_PER_SECOND);
}

void test_unit_moves_in_direction() {
  unit_initialize(&unit);
  unit.throttle = 1.0f;
  unit.direction = HALF_PIf;
  unit_update(&unit, 1.0f);
  assert_position(1.0f * UNIT_PIXELS_PER_SECOND, 0.0f);
}

void assert_position(float x, float y) {
  assert(unit.position.x == x);
  assert(unit.position.y == y);
}
