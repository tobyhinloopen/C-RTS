#include "unit_behavior.h"
#include "../unit/behavior.h"

static void update_unit_behavior(Unit * unit, Game * game) {
  Unit * closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
  Unit * closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);
  Factory * closest_friendly_factory = unit_behavior_find_closest_friendly_factory(unit, world, 32.0f);

  float unit_health = unit_health_percentage(unit);

  if(closest_friendly_factory != NULL)
    unit_behavior_move_away_from(unit, closest_friendly_factory->position);
  else if(closest_friendly_unit != NULL)
    unit_behavior_move_away_from(unit, closest_friendly_unit->position);
  else if(closest_enemy_unit != NULL && unit_health >= 0.5f)
    unit_behavior_set_target_position(unit, closest_enemy_unit->position, 120.0f);
  else if(closest_enemy_unit != NULL)
    unit_behavior_evasive_flee_from(unit, closest_enemy_unit->position);
  else
    unit_behavior_movement_stop(unit);

  if(closest_enemy_unit == NULL)
    unit_behavior_head_stop(unit);
  else if(unit_health < 0.2f && vector_distance(unit->position, closest_enemy_unit->position) < 480.0f)
    unit_behavior_overdrive(unit);
  else
    unit_behavior_head_engage_position(unit, closest_enemy_unit->position);
}

static void update_entity_unit_behavior(Entity * entity, void * game_ptr) {
  if(entity->type == UNIT) {
    update_unit_behavior(&entity->unit, (Game *)game_ptr);
  }
}

static void mod_unit_behavior_update(Game * game, unsigned int delta) {
  world_iterate_entities(&game->world, &game->world, update_entity_unit_behavior);
}

void mod_unit_behavior(GameModule * mod) {
  mod->update = mod_unit_behavior_update;
}
