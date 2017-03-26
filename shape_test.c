#include "shape_test.h"
#include "shape.h"
#include <assert.h>

static void assert_within_delta(float delta, float expected, float actual) {
  assert(expected - actual < delta && actual - expected < delta);
}

static void setup_shape(Shape * shape) {
  shape_alloc(shape, 5);
  shape_add(shape, vector_create(0, 0));
  shape_add(shape, vector_create(2, 0));
  shape_add(shape, vector_create(3, 1));
  shape_add(shape, vector_create(2, 2));
  shape_add(shape, vector_create(0, 2));
  shape_initialize(shape);
}

static void test_shape_initialize() {
  Shape shape;
  setup_shape(&shape);

  assert_within_delta(0.1, 0, shape.bounds_min.x);
  assert_within_delta(0.1, 0, shape.bounds_min.y);
  assert_within_delta(0.1, 3, shape.bounds_max.x);
  assert_within_delta(0.1, 2, shape.bounds_max.y);
}

static void test_shape_contains() {
  Shape shape;
  setup_shape(&shape);

  assert(!shape_contains_point(&shape, vector_create(4, 0)));
  assert(!shape_contains_point(&shape, vector_create(2.6, 0.5)));
  assert(shape_contains_point(&shape, vector_create(2.4, 0.5)));
  assert(shape_contains_point(&shape, vector_create(1, 1)));
}

void test_shape() {
  test_shape_initialize();
  test_shape_contains();
}
