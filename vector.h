#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} Vector;

void vector_initialize(Vector *vector);
void vector_rotate(Vector *vector, float rads);
void vector_add(Vector *vector, Vector other);
void vector_multiply(Vector *vector, Vector other);

#endif
