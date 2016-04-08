#include <math.h>
#include "vector.h"

void vector_initialize(Vector * vector) {
  vector->x = 0;
  vector->y = 0;
}

void vector_rotate(Vector * vector, float radians) {
  float new_x = vector->x * cosf(radians) - vector->y * sinf(radians);
  float new_y = vector->x * sinf(radians) + vector->y * cosf(radians);
  vector->x = new_x;
  vector->y = new_y;
}

void vector_add(Vector * vector, Vector other) {
  vector->x += other.x;
  vector->y += other.y;
}

void vector_subtract(Vector * vector, Vector other) {
  vector->x -= other.x;
  vector->y -= other.y;
}

void vector_multiply(Vector * vector, Vector other) {
  vector->x *= other.x;
  vector->y *= other.y;
}

float vector_distance(Vector a, Vector b) {
  float dx = a.x - b.x;
  float dy = a.y - a.y;
  return sqrtf(dx * dx + dy * dy);
}
