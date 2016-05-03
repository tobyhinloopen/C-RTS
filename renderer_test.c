#include "renderer_test.h"
#include "renderer.h"
#include <assert.h>
#include <stdio.h>
#include "vector.h"

static void assert_vector_equal(Vector expected, Vector actual) {
  if(expected.x != actual.x || expected.y != actual.y) {
    printf("Expected %02f,%02f to equal %02f,%02f\n", actual.x, actual.y, expected.x, expected.y);
    assert(0);
  }
}

static void test_renderer_world_to_screen() {
  Renderer renderer;
  renderer.viewport_width = 200;
  renderer.viewport_height = 100;
  renderer.camera = (Vector3) { 0.0f, 0.0f, 0.0f };

  Vector position = (Vector) { 2.0f, 3.0f };
  assert_vector_equal((Vector) { 102.0f, 53.0f }, renderer_world_to_screen(&renderer, position));

  renderer.camera = (Vector3) { 0.0f, 0.0f, 1.0f };

  assert_vector_equal((Vector) { 101.0f, 51.5f }, renderer_world_to_screen(&renderer, position));
}

void test_renderer() {
  test_renderer_world_to_screen();
}
