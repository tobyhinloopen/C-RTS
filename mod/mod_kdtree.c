#include "mod_kdtree.h"
#include "../kdtree.h"

static void initialize_with_capacity(KDTree * kdtree, size_t capacity) {
  kdtree_initialize(kdtree);
  kdtree_set_capacity(kdtree, capacity);
}

static void mod_kdtree_initialize(Game * game, void * arg) {
  for (int i = 0; i < TEAM_COUNT; i++) {
    initialize_with_capacity(&game->units_kdtrees[i], 1024);
    initialize_with_capacity(&game->factories_kdtrees[i], 1024);
  }
}

static void add_unit_to_kdtree(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  Unit * unit = &entity->unit;
  kdtree_add(&game->units_kdtrees[unit->team_id], unit->position, unit);
}

static void add_factory_to_kdtree(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  Factory * factory = &entity->factory;
  kdtree_add(&game->factories_kdtrees[factory->team_id], factory->position, factory);
}

static void resize_and_build(KDTree * kdtree) {
  if (kdtree->capacity < kdtree->count * 2)
    kdtree_set_capacity(kdtree, kdtree->capacity * 2);
  kdtree_build(kdtree);
}

static void mod_kdtree_update(Game * game, unsigned int delta, void * arg) {
  for (int i = 0; i < TEAM_COUNT; i++) {
    kdtree_clear(&game->units_kdtrees[i]);
    kdtree_clear(&game->factories_kdtrees[i]);
  }

  world_iterate_entities_of_type(&game->world, UNIT, game, add_unit_to_kdtree);
  world_iterate_entities_of_type(&game->world, FACTORY, game, add_factory_to_kdtree);

  for (int i = 0; i < TEAM_COUNT; i++) {
    resize_and_build(&game->units_kdtrees[i]);
    resize_and_build(&game->factories_kdtrees[i]);
  }
}

static void mod_kdtree_deinitialize(Game * game, void * arg) {
  for (int i = 0; i < TEAM_COUNT; i++)
    kdtree_deinitialize(&game->units_kdtrees[i]);
}

void mod_kdtree(GameModule * mod) {
  mod->initialize = mod_kdtree_initialize;
  mod->update = mod_kdtree_update;
  mod->deinitialize = mod_kdtree_deinitialize;
}
