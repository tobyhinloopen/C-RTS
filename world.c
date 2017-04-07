#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "world.h"

static void initialize_world_pool(WorldPool * world_pool) {
  world_pool->entity_pools = NULL;
  world_pool->entity_pool_count = 0;
  world_pool->entity_count = 0;
}

static WorldPool * get_world_pool_for_type(World * world, EntityType type) {
  if (type == UNIT)
    return &world->units;
  if (type == PROJECTILE)
    return &world->projectiles;
  if (type == FACTORY)
    return &world->factories;
  return NULL;
}

void world_initialize(World * world) {
  initialize_world_pool(&world->factories);
  initialize_world_pool(&world->units);
  initialize_world_pool(&world->projectiles);
}

static EntityPool * get_pool_with_available_slot(WorldPool * world_pool) {
  for(int i = 0; i < world_pool->entity_pool_count; ++i) {
    EntityPool * pool = world_pool->entity_pools[i];
    if(pool->entity_count < WORLD_POOL_SIZE)
      return pool;
  }
  return NULL;
}

static Entity * get_none_entity(EntityPool * pool) {
  if (pool->free_count == 0) {
    return &pool->entities[pool->entity_count];
  } else {
    Entity * entity = pool->free[--pool->free_count];
    assert(entity->type == NONE);
    return entity;
  }
}

static EntityPool * allocate_pool(WorldPool * world_pool) {
  ++world_pool->entity_pool_count;
  world_pool->entity_pools = realloc(world_pool->entity_pools, sizeof(EntityPool *) * world_pool->entity_pool_count);
  assert(world_pool->entity_pools != NULL);
  EntityPool * pool = calloc(1, sizeof(EntityPool));
  assert(pool != NULL);
  world_pool->entity_pools[world_pool->entity_pool_count-1] = pool;
  return pool;
}

Entity * world_entity_allocate(World * world, EntityType type) {
  WorldPool * world_pool = get_world_pool_for_type(world, type);
  EntityPool * pool = get_pool_with_available_slot(world_pool);
  if(pool == NULL)
    pool = allocate_pool(world_pool);
  assert(pool != NULL);
  Entity * entity = get_none_entity(pool);
  assert(entity != NULL);
  ++world_pool->entity_count;
  ++pool->entity_count;
  entity->type = type;
  return entity;
}

static void deallocate_pool_entity(WorldPool * world_pool, EntityPool * pool, Entity * entity) {
  assert(entity >= pool->entities && entity <= pool->entities + WORLD_POOL_SIZE);
  entity->type = NONE;
  --pool->entity_count;
  --world_pool->entity_count;
  pool->free[pool->free_count++] = entity;
}

typedef struct {
  float delta;
  EntityPool * entity_pool;
  WorldPool * world_pool;
} UpdateContext;

static void world_unit_update(Entity * entity, void * update_context_ptr) {
  UpdateContext * context = (UpdateContext*)update_context_ptr;
  if (unit_is_dead(&entity->unit))
    deallocate_pool_entity(context->world_pool, context->entity_pool, entity);
  else
    unit_update(&entity->unit, context->delta);
}

static void world_factory_update(Entity * entity, void * update_context_ptr) {
  UpdateContext * context = (UpdateContext*)update_context_ptr;
  if (factory_is_dead(&entity->factory))
    deallocate_pool_entity(context->world_pool, context->entity_pool, entity);
  else
    factory_update(&entity->factory, context->delta);
}

static void world_projectile_update(Entity * entity, void * update_context_ptr) {
  UpdateContext * context = (UpdateContext*)update_context_ptr;
  if (projectile_is_dead(&entity->projectile))
    deallocate_pool_entity(context->world_pool, context->entity_pool, entity);
  else
    projectile_update(&entity->projectile, context->delta);
}

static void pool_iterate_entities(EntityPool * pool, void * arg, void (* fn)(Entity *, void *)) {
  const int len = pool->free_count == 0 ? pool->entity_count : WORLD_POOL_SIZE;
  for(int i = 0; i < len; ++i) {
    Entity * entity = &pool->entities[i];
    if(entity->type != NONE)
      (*fn)(entity, arg);
  }
}

static void world_pool_iterate_entities(WorldPool * world_pool, void * param, void (* fn)(Entity *, void *)) {
  for(int i = 0; i < world_pool->entity_pool_count; ++i)
    pool_iterate_entities(world_pool->entity_pools[i], param, fn);
}

void world_iterate_entities_of_type(World * world, EntityType type, void * param, void (* fn)(Entity *, void *)) {
  world_pool_iterate_entities(get_world_pool_for_type(world, type), param, fn);
}

void world_iterate_entities(World * world, void * param, void (* fn)(Entity *, void *)) {
  world_pool_iterate_entities(&world->units, param, fn);
  world_pool_iterate_entities(&world->factories, param, fn);
  world_pool_iterate_entities(&world->projectiles, param, fn);
}

static void world_pool_update(WorldPool * world_pool, float delta, void (* fn)(Entity *, void *)) {
  UpdateContext update_context = (UpdateContext){ delta, NULL, world_pool };
  for(int i = 0; i < world_pool->entity_pool_count; ++i) {
    update_context.entity_pool = world_pool->entity_pools[i];
    pool_iterate_entities(update_context.entity_pool, &update_context, fn);
  }
}

void world_update(World * world, float delta) {
  world_pool_update(&world->units, delta, world_unit_update);
  world_pool_update(&world->factories, delta, world_factory_update);
  world_pool_update(&world->projectiles, delta, world_projectile_update);
}

static void world_pool_deinitialize(WorldPool * world_pool) {
  for(int i = 0; i < world_pool->entity_pool_count; ++i)
    free(world_pool->entity_pools[i]);
  free(world_pool->entity_pools);
  world_pool->entity_pools = NULL;
}

void world_deinitialize(World * world) {
  world_pool_deinitialize(&world->units);
  world_pool_deinitialize(&world->factories);
  world_pool_deinitialize(&world->projectiles);
}
