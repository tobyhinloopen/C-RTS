#include "mod_closest_factory.h"
#include <assert.h>
#include <float.h>

static void assign_closest_factory(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  Unit * unit = &entity->unit;
  unit->closest_friendly_factory = NULL;
  KDTreeFindResult enemy_best = {NULL, FLT_MAX};
  for (int team_id = 0; team_id < TEAM_COUNT; team_id++) {
    KDTreeFindResult current = kdtree_find_distance(&game->factories_kdtrees[team_id], unit->position);
    if (team_id == unit->team_id) {
      unit->closest_friendly_factory = (Factory *)current.ref;
    } else if(current.distance < enemy_best.distance) {
      enemy_best = current;
    }
  }
  unit->closest_enemy_factory = (Factory *)enemy_best.ref;
}

static void mod_closest_factory_update(Game * game, unsigned int delta) {
  world_iterate_entities_of_type(&game->world, UNIT, game, assign_closest_factory);
}

void mod_closest_factory(GameModule * mod) {
  mod->update = mod_closest_factory_update;
}
