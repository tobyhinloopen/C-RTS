#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} Vector;

void vector_initialize(Vector * vector);
void vector_rotate(Vector * vector, float rads);
void vector_add(Vector * vector, Vector other);
void vector_subtract(Vector * vector, Vector other);
void vector_multiply(Vector * vector, Vector other);
float vector_distance(Vector a, Vector b);
float vector_angle(Vector vector);
float vector_angle_between(Vector a, Vector b);

#endif
