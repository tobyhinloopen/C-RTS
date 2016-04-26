#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} Vector;

void vector_initialize(Vector *);
void vector_rotate(Vector *, float rads);
void vector_add(Vector *, Vector other);
void vector_subtract(Vector *, Vector other);
void vector_multiply(Vector *, Vector other);
void vector_multiply_scalar(Vector *, float scalar);
float vector_distance(Vector a, Vector b);
float vector_angle(Vector);
float vector_angle_between(Vector a, Vector b);

#endif
