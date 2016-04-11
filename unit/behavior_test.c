#include <assert.h>
#include "behavior_test.h"
#include "behavior.h"
#include "../vector.h"
#include "../unit.h"
#include "../pi.h"

static Unit create_sample_unit() {
  Unit unit;
  unit_initialize(&unit);
  return unit;
}

static void test_unit_behavior_look_at() {
  Unit unit = create_sample_unit();
  unit_behavior_look_at(&unit, (Vector) { 1.0f, 1.0f });
  assert(unit.head_throttle == 1.0f);
  unit_behavior_look_at(&unit, (Vector) { 1.0f, -1.0f });
  assert(unit.head_throttle == -1.0f);
}

static void test_unit_behavior_look_forward() {
  Unit unit = create_sample_unit();
  unit.head_direction = PI * 0.5f;
  unit_behavior_look_forward(&unit);
  assert(unit.head_throttle == -1.0f);
  unit.head_direction = PI * 1.5f;
  unit_behavior_look_forward(&unit);
  assert(unit.head_throttle == 1.0f);
}

static void test_unit_behavior_set_target_position() {
  Unit unit = create_sample_unit();
  unit_behavior_set_target_position(&unit, (Vector) { 1.0f, 1.0f }, 0);
  assert(unit.angular_throttle == 1.0f);
  assert(unit.throttle == 1.0f);
}

void test_unit_behavior() {
  test_unit_behavior_look_at();
  test_unit_behavior_look_forward();
  test_unit_behavior_set_target_position();
}
