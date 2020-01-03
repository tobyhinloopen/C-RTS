#include "mod_scalable_grid.h"
#include "../scalable_grid.h"
#include "../config.h"

#ifdef CONFIG_SCALABLE_GRID_ENABLED

static void mod_scalable_grid_initialize(Game * game, void * arg) {
  scalable_grid_initialize(&game->scalable_grid);
  scalable_grid_set_size(&game->scalable_grid, (GridXY){ CONFIG_SCALABLE_GRID_SIZE, CONFIG_SCALABLE_GRID_SIZE });
  scalable_grid_set_transform(&game->scalable_grid, (Vector){ -2048, -2048 }, (Vector){ 4096, 4096 });
  scalable_grid_set_capacity(&game->scalable_grid, CONFIG_SCALABLE_GRID_INITIAL_CAPACITY);
}

static Vector * entity_position(Entity * entity) {
  if (entity->type == UNIT) {
    return &entity->unit.position;
  } else if(entity->type == FACTORY) {
    return &entity->factory.position;
  } else {
    return NULL;
  }
}

static void world_entity_scalable_grid_insert(Entity * entity, void * scalable_grid_ptr) {
  ScalableGrid * scalable_grid = (ScalableGrid *)scalable_grid_ptr;
  Vector * position = entity_position(entity);
  if (position != NULL) {
    scalable_grid_put(scalable_grid, *position, entity);
  }
}

typedef struct {
  unsigned int count;
  Vector min;
  Vector max;
} VectorCountMinMax;

static void world_entity_count_min_max(Entity * entity, void * count_min_max_ptr) {
  VectorCountMinMax * c = (VectorCountMinMax *)count_min_max_ptr;
  Vector * p = entity_position(entity);
  if (p != NULL) {
    if (c->count == 0 || c->min.x > p->x) c->min.x = p->x;
    if (c->count == 0 || c->min.y > p->y) c->min.y = p->y;
    if (c->count == 0 || c->max.x < p->x) c->max.x = p->x;
    if (c->count == 0 || c->max.y < p->y) c->max.y = p->y;
    c->count++;
  }
}

static void ensure_capacity(ScalableGrid * scalable_grid, unsigned int required_capacity) {
  if (required_capacity > scalable_grid->grid.items_capacity)
    scalable_grid_set_capacity(scalable_grid, required_capacity * 2);
}

static void mod_scalable_grid_update(Game * game, unsigned int delta, void * arg) {
  VectorCountMinMax c = {0, {0, 0}, {0, 0}};
  world_iterate_entities_of_type(&game->world, UNIT, &c, world_entity_count_min_max);
  world_iterate_entities_of_type(&game->world, FACTORY, &c, world_entity_count_min_max);

  scalable_grid_set_transform(&game->scalable_grid, c.min, c.max);
  ensure_capacity(&game->scalable_grid, c.count);

  scalable_grid_clear(&game->scalable_grid);
  world_iterate_entities_of_type(&game->world, UNIT, &game->scalable_grid, world_entity_scalable_grid_insert);
  world_iterate_entities_of_type(&game->world, FACTORY, &game->scalable_grid, world_entity_scalable_grid_insert);
}

static void mod_scalable_grid_deinitialize(Game * game, void * arg) {
  scalable_grid_deinitialize(&game->scalable_grid);
}

void mod_scalable_grid(GameModule * mod) {
  mod->initialize = mod_scalable_grid_initialize;
  mod->update = mod_scalable_grid_update;
  mod->deinitialize = mod_scalable_grid_deinitialize;
}

#endif
