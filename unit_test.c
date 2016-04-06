#include <assert.h>
#include "unit_test.h"
#include "unit.h"
#include "pi.h"

Unit unit;

void test_unit_without_throttle_doesnt_move();
void test_unit_without_delta_doesnt_move();
void test_unit_with_throttle_and_delta_does_move();
void text_unit_with_throttle_and_angular_throttle_turns_half_a_circle();
void test_unit_moves_in_direction();
void assert_position(float x, float y);
void assert_position_within_delta(float x, float y, float delta);

void test_unit() {
  test_unit_initialize();
  test_unit_update();
}

void test_unit_initialize() {
  unit_initialize(&unit);
  assert_position(0, 0);
  assert(unit.direction == 0);
  assert(unit.throttle == 0);
}

void test_unit_update() {
  test_unit_without_throttle_doesnt_move();
  test_unit_without_delta_doesnt_move();
  test_unit_with_throttle_and_delta_does_move();
  text_unit_with_throttle_and_angular_throttle_turns_half_a_circle();
}

void test_unit_without_throttle_doesnt_move() {
  unit_initialize(&unit);
  unit.throttle = 0;
  unit_update(&unit, 1);
  assert_position(0, 0);
}

void test_unit_without_delta_doesnt_move() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit_update(&unit, 0);
  assert_position(0, 0);
}

void test_unit_with_throttle_and_delta_does_move() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit_update(&unit, 1);
  assert_position(0, 1 * UNIT_PIXELS_PER_SECOND);
}

void text_unit_with_throttle_and_angular_throttle_turns_half_a_circle() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit.angular_throttle = -1;
  unit_update(&unit, PIf / UNIT_RADIANS_PER_SECOND);
  assert_position_within_delta(UNIT_PIXELS_PER_SECOND / HALF_PIf, 0, 0.05);
}

void test_unit_moves_in_direction() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit.direction = HALF_PIf;
  unit_update(&unit, 1);
  assert_position(1 * UNIT_PIXELS_PER_SECOND, 0);
}

void assert_position(float x, float y) {
  assert(unit.position.x == x);
  assert(unit.position.y == y);
}

void assert_position_within_delta(float x, float y, float delta) {
  //printf("assert %fx%f to equal %fx%f (delta %f)\n", unit.position.x, unit.position.y, x, y, delta);
  assert(unit.position.x > x - delta && unit.position.x < x + delta);
  assert(unit.position.y > y - delta && unit.position.y < y + delta);
}
