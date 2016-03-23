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

void world_initialize(World *world);
WorldUnit * world_unit_allocate(World *world);
void world_unit_deallocate(World *world, WorldUnit *unit);
void world_update(World *world, float delta);
void world_iterate_units(World * world, void (*)(Unit *));
void world_deinitialize(World *world);

#endif
