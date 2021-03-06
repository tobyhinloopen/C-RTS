#include "mod_closest_friendly_unit.h"

static void assign_closest_friendly_unit(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  Unit * unit = &entity->unit;
  KDTreeFindResult best = kdtree_find_distance_excluding(&game->units_kdtrees[unit->team_id], unit->position, unit);
  unit->closest_friendly_unit = (Unit *)best.ref;
}

static void mod_closest_friendly_unit_update(Game * game, unsigned int delta, void * arg) {
  world_iterate_entities_of_type(&game->world, ENTITY_UNIT, game, assign_closest_friendly_unit);
}

void mod_closest_friendly_unit(GameModule * mod) {
  mod->update = mod_closest_friendly_unit_update;
}
