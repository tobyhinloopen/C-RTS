#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "shape.h"

typedef struct {
  Vector size;
  Vector * spawn_points;
  int spawn_points_count;
  Shape * shapes;
  int shapes_count;
} Map;

void map_initialize(Map *, int spawn_points_count, int shapes_count);
void map_deinitialize(Map *);

#endif
