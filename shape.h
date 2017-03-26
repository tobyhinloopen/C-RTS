#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"

typedef struct {
  Vector bounds_min;
  Vector bounds_max;
  int count;
  int capacity;
  Vector * points;
} Shape;

void shape_alloc(Shape *, int);
void shape_add(Shape *, Vector);
void shape_initialize(Shape *);
int shape_contains_point(Shape *, Vector);
void shape_free(Shape * shape);

#endif
