#include "mod_grid.h"
#include "../grid.h"

void mod_grid_initialize(Game * game) {
  grid_initialize(&game->grid);
  grid_set_size(&game->grid, (GridXY){ 128, 128 });
  grid_set_capacity(&game->grid, 4096);
}

static void world_entity_grid_insert(Entity * entity, void * grid_ptr) {
  Vector posf;

  if (entity->type == UNIT) {
    posf = entity->unit.position;
  } else if(entity->type == FACTORY) {
    posf = entity->factory.position;
  }

  if (entity->type == UNIT || entity->type == FACTORY) {
    grid_put((Grid *)grid_ptr, (GridXY){48 + posf.x / 64.f, 48 + posf.y / 64.f}, entity);
  }
}

static void mod_grid_update(Game * game, unsigned int delta) {
  grid_clear(&game->grid);
  world_iterate_entities(&game->world, &game->grid, world_entity_grid_insert);
}

static void mod_grid_deinitialize(Game * game) {
  grid_deinitialize(&game->grid);
}

void mod_grid(GameModule * mod) {
  mod->initialize = mod_grid_initialize;
  mod->update = mod_grid_update;
  mod->deinitialize = mod_grid_deinitialize;
}
