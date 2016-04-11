#include <assert.h>
#include "vector_test.h"
#include "vector.h"
#include "pi.h"

static void assert_within_delta(float delta, float expected, float actual) {
  assert(expected - actual < delta && actual - expected < delta);
}

static void test_vector_angle() {
  assert_within_delta(0.01, PI*0.25, vector_angle((Vector){ 1, 1 }));
}

static void test_vector_angle_between() {
  assert_within_delta(0.01, PI*0.25, vector_angle_between((Vector){ 0, 0 }, (Vector){ 1, 1 }));
}

void test_vector() {
  test_vector_angle();
  test_vector_angle_between();
}
