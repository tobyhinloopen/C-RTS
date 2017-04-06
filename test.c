#include "test.h"

#include "unit_test.h"
#include "world_test.h"
#include "vector_test.h"
#include "unit/behavior_test.h"
#include "renderer_test.h"
#include "shape_test.h"
#include "factory_test.h"
#include "grid_test.h"
#include "kdtree_test.h"
#include "rand_range_test.h"

#include <stdio.h>

void test() {
  test_unit();
  test_world();
  test_vector();
  test_unit_behavior();
  test_renderer();
  test_shape();
  test_factory();
  test_grid();
  test_kdtree();
  test_rand_range();
  printf("TEST OK\n");
}
