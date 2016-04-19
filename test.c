#include "test.h"
#include "unit_test.h"
#include "world_test.h"
#include "vector_test.h"
#include "unit/behavior_test.h"
#include "renderer_test.h"

void test() {
  test_unit();
  test_world();
  test_vector();
  test_unit_behavior();
  test_renderer();
}
