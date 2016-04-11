#include <assert.h>
#include <stdio.h>
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
  assert_position(0, UNIT_PIXELS_PER_SECOND);
}

void text_unit_with_throttle_and_angular_throttle_turns_half_a_circle() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit.angular_throttle = -1;
  unit_update(&unit, PI / UNIT_RADIANS_PER_SECOND);
  assert_position_within_delta(0, UNIT_PIXELS_PER_SECOND / UNIT_RADIANS_PER_SECOND * 2, 0.05);
}

void test_unit_moves_in_direction() {
  unit_initialize(&unit);
  unit.throttle = 1;
  unit.direction = HALF_PI;
  unit_update(&unit, 1);
  assert_position(0, UNIT_PIXELS_PER_SECOND);
}

void assert_position(float x, float y) {
  assert(unit.position.x == x);
  assert(unit.position.y == y);
}

void assert_position_within_delta(float x, float y, float delta) {
  int assertion_result = unit.position.x > x - delta && unit.position.x < x + delta
    && unit.position.y > y - delta && unit.position.y < y + delta;
  if(!assertion_result)
    printf("assert %7.1f,%7.1f to equal %7.1fx%7.1f (delta %f)\n",
      unit.position.x, unit.position.y, x, y, delta);
  assert(assertion_result);
}
