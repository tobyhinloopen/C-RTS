#include <stdlib.h>
#include <assert.h>
#include "world.h"

const unsigned int REALLOC_UNITS_INCREMENT = 256;
void world_increase_unit_pool_size(World * world);

void world_initialize(World * world) {
  world->unit_count = 0;
  world->unit_pool_size = 0;
  world->units = NULL;
}

WorldUnit * world_unit_allocate(World * world) {
  if(world->unit_count >= world->unit_pool_size)
    world_increase_unit_pool_size(world);
  WorldUnit * world_unit = &world->units[world->unit_count++];
  world_unit->alive = 1;
  return world_unit;
}

void world_unit_deallocate(World * world, WorldUnit * world_unit) {
  world_unit->alive = 0;
  world->unit_count--;
}

void world_update(World * world, float delta) {
  int unit_index = 0;
  int world_unit_index = 0;
  while(unit_index < world->unit_count) {
    WorldUnit * world_unit = &world->units[world_unit_index++];
    if(world_unit->alive) {
      unit_index++;
      unit_update(&world_unit->unit, delta);
    }
  }
}

void world_deinitialize(World * world) {
  free(world->units);
}

void world_increase_unit_pool_size(World * world) {
  world->unit_pool_size += REALLOC_UNITS_INCREMENT;
  world->units = realloc(world->units, sizeof(WorldUnit) * world->unit_pool_size);
  assert(world->units != NULL);
}
