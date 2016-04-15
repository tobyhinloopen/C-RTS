#ifndef WORLD_H
#define WORLD_H

#include "unit.h"
#include "projectile.h"

#define WORLD_POOL_SIZE 8192

typedef enum { NONE = 0, UNIT, PROJECTILE } EntityType;

typedef struct {
  EntityType type;
  union {
    Unit unit;
    Projectile projectile;
  };
} Entity;

typedef struct {
  Entity entities[WORLD_POOL_SIZE];
  int entity_count;
} EntityPool;

typedef struct {
  float time;
  EntityPool ** entity_pools;
  int entity_pool_count;
} World;

void world_initialize(World *);
Entity * world_entity_allocate(World *, EntityType type);
void world_entity_deallocate(World *, Entity *);
void world_update(World *, float delta);
void world_iterate_entities(World *, void *, void (*)(Entity *, void *));
void world_deinitialize(World *);

#endif
