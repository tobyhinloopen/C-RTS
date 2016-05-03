#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct {
  float x;
  float y;
  float z;
} Vector3;

void vector3_add(Vector3 *, Vector3);
void vector3_subtract(Vector3 *, Vector3);
void vector3_multiply(Vector3 *, Vector3);
void vector3_multiply_scalar(Vector3 *, float scalar);

#endif
