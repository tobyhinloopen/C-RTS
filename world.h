#ifndef WORLD_H
#define WORLD_H

#include "unit.h"

typedef struct {
  unsigned char alive;
  Unit unit;
} WorldUnit;

typedef struct {
  float time;
  WorldUnit *units;
  unsigned int unit_count;
  unsigned int unit_pool_size;
} World;

void world_initialize(World *);
WorldUnit * world_unit_allocate(World *);
void world_unit_deallocate(World *, WorldUnit *);
void world_update(World *, float delta);
void world_iterate_units(World *, void *, void (*)(Unit *, void *));
void world_deinitialize(World *);

#endif
