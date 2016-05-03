#include <math.h>
#include "vector3.h"

void vector3_add(Vector3 * vector, Vector3 other) {
  vector->x += other.x;
  vector->y += other.y;
  vector->z += other.z;
}

void vector3_subtract(Vector3 * vector, Vector3 other) {
  vector->x -= other.x;
  vector->y -= other.y;
  vector->z -= other.z;
}

void vector3_multiply(Vector3 * vector, Vector3 other) {
  vector->x *= other.x;
  vector->y *= other.y;
  vector->z *= other.z;
}

void vector3_multiply_scalar(Vector3 * vector, float scalar) {
  vector->x *= scalar;
  vector->y *= scalar;
  vector->z *= scalar;
}
