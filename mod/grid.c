#include "grid.h"
#include "../grid.h"

void mod_grid_initialize(Game * game) {
  grid_initialize(&game->grid);
  grid_set_size(&game->grid, (GridXY){ 128, 128 });
  grid_set_capacity(&game->grid, 32768);
}

static void world_entity_grid_insert(Entity * entity, void * grid_ptr) {
  if (entity->type == UNIT) {
    Grid * grid = (Grid *)grid_ptr;
    GridXY pos;
    pos.x = 48 + entity->unit.position.x / 64.f;
    pos.y = 48 + entity->unit.position.y / 64.f;
    grid_put(grid, pos, &entity->unit);
  }
}

void mod_grid_update(Game * game, unsigned int delta) {
  grid_clear(&game->grid);
  world_iterate_entities(&game->world, &game->grid, world_entity_grid_insert);
}

void mod_grid_deinitialize(Game * game) {
  grid_deinitialize(&game->grid);
}

void mod_grid(GameModule * mod) {
  mod->initialize = mod_grid_initialize;
  mod->update = mod_grid_update;
  mod->deinitialize = mod_grid_deinitialize;
}
