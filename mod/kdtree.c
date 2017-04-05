#include "kdtree.h"
#include "../kdtree.h"

void mod_kdtree_initialize(Game * game) {
  for (int i = 0; i < TEAM_COUNT; i++) {
    kdtree_initialize(&game->kdtree[i]);
    kdtree_set_capacity(&game->kdtree[i], 2048);
  }
}

static void add_unit_to_kdtree(Entity * entity, void * game_ptr) {
  if (entity->type == UNIT) {
    Game * game = (Game *)game_ptr;
    Unit * unit = &entity->unit;
    kdtree_add(&game->kdtree[unit->team_id], unit->position, unit);
  }
}

void mod_kdtree_update(Game * game, unsigned int delta) {
  for (int i = 0; i < TEAM_COUNT; i++)
    kdtree_clear(&game->kdtree[i]);
  world_iterate_entities(&game->world, game, add_unit_to_kdtree);
  for (int i = 0; i < TEAM_COUNT; i++)
    kdtree_build(&game->kdtree[i]);
}

void mod_kdtree_deinitialize(Game * game) {
  for (int i = 0; i < TEAM_COUNT; i++)
    kdtree_deinitialize(&game->kdtree[i]);
}

void mod_kdtree(GameModule * mod) {
  mod->initialize = mod_kdtree_initialize;
  mod->update = mod_kdtree_update;
  mod->deinitialize = mod_kdtree_deinitialize;
}
