#include "mod_closest_enemy_unit.h"
#include <float.h>
#include "../config.h"

static void assign_closest_enemy_unit(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  Unit * unit = &entity->unit;
  KDTreeFindResult best = {NULL, FLT_MAX};
  for (int team_id = 0; team_id < TEAM_COUNT; team_id++) {
    if (team_id != unit->team_id) {
      KDTreeFindResult current = kdtree_find_distance(&game->units_kdtrees[team_id], unit->position);
      if (current.distance < best.distance) {
        best = current;
      }
    }
  }
  unit->closest_enemy_unit = (Unit *)best.ref;
}

static void mod_closest_enemy_unit_update(Game * game, unsigned int delta) {
  world_iterate_entities_of_type(&game->world, UNIT, game, assign_closest_enemy_unit);
}

void mod_closest_enemy_unit(GameModule * mod) {
  mod->update = mod_closest_enemy_unit_update;
}
