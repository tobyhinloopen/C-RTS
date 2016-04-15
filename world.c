#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "world.h"
#include <stdio.h>

static EntityPool * allocate_pool(World * world) {
  ++world->entity_pool_count;
  world->entity_pools = realloc(world->entity_pools, sizeof(EntityPool*) * world->entity_pool_count);
  assert(world->entity_pools != NULL);
  EntityPool * pool = calloc(1, sizeof(EntityPool));
  assert(pool != NULL);
  world->entity_pools[world->entity_pool_count-1] = pool;
  return pool;
}

void world_initialize(World * world) {
  world->time = 0.0f;
  world->entity_pools = NULL;
  world->entity_pool_count = 0;
}

static EntityPool * get_pool_with_available_slot(World * world) {
  for(int i = 0; i < world->entity_pool_count; ++i) {
    EntityPool * pool = world->entity_pools[i];
    if(pool->entity_count < WORLD_POOL_SIZE)
      return pool;
  }
  return NULL;
}

static Entity * get_none_entity(EntityPool * pool) {
  for(int i = 0; i < WORLD_POOL_SIZE; i++) {
    Entity * entity = &pool->entities[i];
    if(entity->type == NONE)
      return entity;
  }
  return NULL;
}

Entity * world_entity_allocate(World * world, EntityType type) {
  EntityPool * pool = get_pool_with_available_slot(world);
  if(pool == NULL)
    pool = allocate_pool(world);
  assert(pool != NULL);
  Entity * entity = get_none_entity(pool);
  assert(entity != NULL);
  ++pool->entity_count;
  entity->type = type;
  return entity;
}

static void world_entity_update(Entity * entity, void * delta_ptr) {
  float delta = *((float*)delta_ptr);
  switch(entity->type) {
    case UNIT:
      if(unit_is_dead(&entity->unit))
        entity->type = NONE;
      else
        unit_update(&entity->unit, delta);
      break;
    case PROJECTILE:
      if(projectile_is_dead(&entity->projectile))
        entity->type = NONE;
      else
        projectile_update(&entity->projectile, delta);
      break;
    case NONE:
      break;
  }
}

static void pool_iterate_entities(EntityPool * pool, void * arg, void (* fn)(Entity *, void *)) {
  for(int i = 0; i < WORLD_POOL_SIZE; ++i) {
    Entity * entity = &pool->entities[i];
    if(entity->type != NONE)
      (*fn)(entity, arg);
  }
}

void world_iterate_entities(World * world, void * arg, void (* fn)(Entity *, void *)) {
  for(int i = 0; i < world->entity_pool_count; ++i)
    pool_iterate_entities(world->entity_pools[i], arg, fn);
}

static void count_pool_entities(EntityPool * pool) {
  int count = 0;
  for(int i = 0; i < WORLD_POOL_SIZE; ++i)
    if(pool->entities[i].type != NONE)
      ++count;
  pool->entity_count = count;
}

void world_update(World * world, float delta) {
  printf("POOL COUNT %d\n", world->entity_pool_count);
  world_iterate_entities(world, &delta, world_entity_update);

  for(int i = 0; i < world->entity_pool_count; ++i)
    count_pool_entities(world->entity_pools[i]);
}

void world_deinitialize(World * world) {
  for(int i = 0; i < world->entity_pool_count; ++i)
    free(world->entity_pools[i]);
  free(world->entity_pools);
}
