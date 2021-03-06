#include <math.h>
#include "vector.h"
#include "pi.h"

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

void vector_multiply_scalar(Vector * vector, float scalar) {
  vector->x *= scalar;
  vector->y *= scalar;
}

float vector_sq_distance(Vector a, Vector b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return dx * dx + dy * dy;
}

float vector_distance(Vector a, Vector b) {
  return sqrtf(vector_sq_distance(a, b));
}

float vector_angle(Vector vector) {
  return atan2f(vector.y, vector.x);
}

float vector_angle_between(Vector a, Vector b) {
  vector_subtract(&b, a);
  return vector_angle(b);
}

Vector vector_create(float x, float y) {
  Vector vector;
  vector.x = x;
  vector.y = y;
  return vector;
}
