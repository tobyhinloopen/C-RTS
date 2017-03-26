#include "test.h"

#include <stdio.h>

#include "unit_test.h"
#include "world_test.h"
#include "vector_test.h"
#include "unit/behavior_test.h"
#include "renderer_test.h"
#include "shape_test.h"
#include "factory_test.h"

void test() {
  test_unit();
  printf("test_unit OK\n");

  test_world();
  printf("test_world OK\n");

  test_vector();
  printf("test_vector OK\n");

  test_unit_behavior();
  printf("test_unit_behavior OK\n");

  test_renderer();
  printf("test_renderer OK\n");

  test_shape();
  printf("test_shape OK\n");

  test_factory();
  printf("test_factory OK\n");
}
