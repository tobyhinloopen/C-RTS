#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "world.h"

const int REALLOC_ENTITIES_INCREMENT = 256;

void world_initialize(World * world) {
  world->entity_count = 0;
  world->entity_pool_size = 0;
  world->entities = NULL;
}

static void world_increase_entity_pool_size(World * world) {
  const size_t old_size = world->entity_pool_size;
  world->entity_pool_size += REALLOC_ENTITIES_INCREMENT;
  world->entities = realloc(world->entities, sizeof(Entity) * world->entity_pool_size);
  assert(world->entities != NULL);
  memset(world->entities + old_size, 0, sizeof(Entity) * (world->entity_pool_size - old_size));
}

Entity * world_entity_allocate(World * world, EntityType type) {
  if(world->entity_count >= world->entity_pool_size)
    world_increase_entity_pool_size(world);
  Entity * entity = &world->entities[world->entity_count++];
  entity->type = type;
  return entity;
}

void world_entity_deallocate(World * world, Entity * entity) {
  entity->type = NONE;
  world->entity_count--;
}

static void world_entity_update(Entity * entity, void * delta_ptr) {
  float delta = *((float*)delta_ptr);
  switch(entity->type) {
    case UNIT: unit_update(&entity->unit, delta); break;
    case PROJECTILE: projectile_update(&entity->projectile, delta); break;
    case NONE: break;
  }
}

void world_update(World * world, float delta) {
  world_iterate_entities(world, &delta, world_entity_update);
}

void world_iterate_entities(World * world, void * arg, void (* fn)(Entity *, void *)) {
  Entity * entity_end = &world->entities[world->entity_pool_size];
  for(Entity * entity = world->entities; entity < entity_end; entity++)
    if(entity->type != NONE)
      (*fn)(entity, arg);
}

void world_deinitialize(World * world) {
  free(world->entities);
}
