#include "map.h"
#include <assert.h>
#include <stdlib.h>

void map_initialize(Map * map, int spawn_points_count, int shapes_count) {
  map->size.x = 0;
  map->size.y = 0;

  map->spawn_points_count = spawn_points_count;
  map->spawn_points = (Vector *)malloc(sizeof(Vector) * spawn_points_count);
  assert(map->spawn_points != NULL);

  map->shapes_count = shapes_count;
  map->shapes = (Shape *)malloc(sizeof(Shape) * shapes_count);
  assert(map->shapes != NULL);
}

void map_deinitialize(Map * map) {
  free(map->shapes);
  map->shapes = NULL;
  free(map->spawn_points);
  map->spawn_points = NULL;
}
