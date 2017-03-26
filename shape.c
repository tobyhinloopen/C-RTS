#include "shape.h"
#include <assert.h>
#include <stdlib.h>

void shape_alloc(Shape * shape, int capacity) {
  shape->points = (Vector *) malloc(sizeof(Vector) * capacity);
  assert(shape->points != NULL);

  shape->capacity = capacity;
  shape->count = 0;
}

void shape_add(Shape * shape, Vector point) {
  assert(shape->capacity >= shape->count);

  shape->points[shape->count] = point;
  ++shape->count;
}

static void update_bounds_min_max(Shape * shape, Vector p) {
  if (p.x < shape->bounds_min.x) shape->bounds_min.x = p.x;
  if (p.y < shape->bounds_min.y) shape->bounds_min.y = p.y;
  if (p.x > shape->bounds_max.x) shape->bounds_max.x = p.x;
  if (p.y > shape->bounds_max.y) shape->bounds_max.y = p.y;
}

void shape_initialize(Shape * shape) {
  vector_initialize(&shape->bounds_min);
  vector_initialize(&shape->bounds_max);

  for (size_t i = 0; i < shape->count; ++i)
    update_bounds_min_max(shape, shape->points[i]);
}

static int shape_bounds_contains_point(Shape * shape, Vector p) {
  return p.x >= shape->bounds_min.x
      && p.x <= shape->bounds_max.x
      && p.y >= shape->bounds_min.y
      && p.y <= shape->bounds_max.y;
}

// See: http://stackoverflow.com/a/2922778
// See: http://stackoverflow.com/a/8721483
static int shape_polygon_contains_point(Shape * shape, Vector p) {
  int i, j, c = 0;
  for (i = 0, j = shape->count - 1; i < shape->count; j = i++) {
    Vector vi = shape->points[i];
    Vector vj = shape->points[j];
    if (vi.y > p.y != vj.y > p.y && p.x < (vj.x - vi.x) * (p.y - vi.y) / (vj.y - vi.y) + vi.x) {
      c = !c;
    }
  }
  return c;
}

int shape_contains_point(Shape * shape, Vector point) {
  return shape_bounds_contains_point(shape, point) && shape_polygon_contains_point(shape, point);
}

void shape_free(Shape * shape) {
  free(shape->points);
  shape->points = NULL;
}
