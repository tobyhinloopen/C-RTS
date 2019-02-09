#ifndef WORLD_H
#define WORLD_H

#include "unit.h"
#include "projectile.h"
#include "factory.h"

#define WORLD_POOL_SIZE 32

#define WORLD_ITERATE_ENTITIES(world, ...) \
  WORLD_POOL_ITERATE_ENTITIES(&((world)->units), __VA_ARGS__); \
  WORLD_POOL_ITERATE_ENTITIES(&((world)->factories), __VA_ARGS__); \
  WORLD_POOL_ITERATE_ENTITIES(&((world)->projectiles), __VA_ARGS__); \

#define WORLD_POOL_ITERATE_ENTITIES(world_pool, ...) \
  for (int _wpi = 0; _wpi < (world_pool)->entity_pool_count; ++_wpi) { \
    const EntityPool * _entity_pool = (world_pool)->entity_pools[_wpi]; \
    const int _entity_pool_length = _entity_pool->free_count == 0 ? _entity_pool->entity_count : WORLD_POOL_SIZE; \
    for (int _epi = 0; _epi < _entity_pool_length; ++_epi) { \
      const Entity * entity = &_entity_pool->entities[_epi]; \
      if(entity->type != NONE) { \
        __VA_ARGS__ \
      } \
    } \
  } \

typedef enum { NONE = 0, UNIT, PROJECTILE, FACTORY } EntityType;

typedef struct {
  EntityType type;
  union {
    Unit unit;
    Projectile projectile;
    Factory factory;
  };
} Entity;

typedef struct {
  Entity entities[WORLD_POOL_SIZE];
  unsigned int entity_count;
  Entity * free[WORLD_POOL_SIZE];
  unsigned int free_count;
} EntityPool;

typedef struct {
  EntityPool ** entity_pools;
  unsigned int entity_pool_count;
  unsigned int entity_count;
} WorldPool;

typedef struct {
  WorldPool units;
  WorldPool projectiles;
  WorldPool factories;
} World;

void world_initialize(World *);
Entity * world_entity_allocate(World *, EntityType type);
void world_update(World *, float delta);
void world_iterate_entities(World *, void *, void (*)(Entity *, void *));
void world_pool_iterate_entities(WorldPool * world_pool, void * param, void (* fn)(Entity *, void *));
void world_iterate_entities_of_type(World *, EntityType type, void *, void (*)(Entity *, void *));
void world_deinitialize(World *);

#endif
