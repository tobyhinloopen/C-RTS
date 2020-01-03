#include "mod_unit_behavior.h"
#include "../unit/behavior.h"
#include <float.h>

#define OVERDRIVE_DISTANCE 480
#define FLEE_DISTANCE 960
#define FRIENDLY_UNIT_DISTANCE_SQ (32 * 32)
#define FRIENDLY_FACTORY_DISTANCE_SQ (32 * 32)

static Vector get_closest_point_inside(Map * map, Vector pos, float distance) {
  const float max_x = map->size.x - distance;
  if (pos.x < distance)
    pos.x = distance;
  else if (pos.x > max_x)
    pos.x = max_x;

  const float max_y = map->size.y - distance;
  if (pos.y < distance)
    pos.y = distance;
  else if (pos.y > max_y)
    pos.y = max_y;
  return pos;
}

static int engage_enemy_factory(Unit * unit, Game * game) {
  if(unit->closest_enemy_factory) {
    unit_behavior_head_engage_position(unit, unit->closest_enemy_factory->position);
    return 1;
  }
  return 0;
}

static int engage_enemy_unit(Unit * unit, Game * game) {
  if(unit->closest_enemy_unit) {
    unit_behavior_head_engage_position(unit, unit->closest_enemy_unit->position);
    return 1;
  }
  return 0;
}

static int engage_idle(Unit * unit, Game * game) {
  unit_behavior_head_stop(unit);
  return 0;
}

static void engage_enemy(Unit * unit, Game * game) {
  engage_enemy_unit(unit, game)
  || engage_enemy_factory(unit, game)
  || engage_idle(unit, game);
}

static int move_inside_map(Unit * unit, Game * game) {
  if (unit->position.x < 0
  || unit->position.x > game->map.size.x
  || unit->position.y < 0
  || unit->position.y > game->map.size.y) {
    unit_behavior_set_target_position(unit, get_closest_point_inside(&game->map, unit->position, 64.0f), 32.0f);
    return 1;
  }
  return 0;
}

static int move_away_from_colliding_friendly_factory(Unit * unit, Game * game) {
  if (unit->closest_friendly_factory != NULL
  && vector_sq_distance(unit->position, unit->closest_friendly_factory->position) <= FRIENDLY_FACTORY_DISTANCE_SQ) {
    unit_behavior_move_away_from(unit, unit->closest_friendly_factory->position);
    return 1;
  }
  return 0;
}

static int move_away_from_colliding_friendly_unit(Unit * unit, Game * game) {
  if (unit->closest_friendly_unit != NULL
  && vector_sq_distance(unit->position, unit->closest_friendly_unit->position) <= FRIENDLY_UNIT_DISTANCE_SQ) {
    unit_behavior_move_away_from(unit, unit->closest_friendly_unit->position);
    return 1;
  }
  return 0;
}

static int move_to_target_position(Unit * unit, Game * game) {
  if (unit->mode & UNIT_MODE_FORCE_MOVE_TARGET_POSITION) {
    if (vector_distance(unit->target_position, unit->position) < 128.0f) {
      unit->mode = 0;
    } else {
      unit_behavior_set_target_position(unit, unit->target_position, 16.0f);
    }
    return 1;
  }
  return 0;
}

static int move_away_from_enemy_unit(Unit * unit, Game * game) {
  if (unit->closest_enemy_unit != NULL
  && unit_health_percentage(unit) < 0.5f
  && vector_distance(unit->position, unit->closest_enemy_unit->position) < FLEE_DISTANCE) {
    unit_behavior_evasive_flee_from(unit, unit->closest_enemy_unit->position);
    return 1;
  }
  return 0;
}

static int move_to_enemy_unit(Unit * unit, Game * game) {
  if (unit->closest_enemy_unit != NULL) {
    unit_behavior_set_target_position(unit, unit->closest_enemy_unit->position, 120.0f);
    return 1;
  }
  return 0;
}

static int move_to_enemy_factory(Unit * unit, Game * game) {
  if (unit->closest_enemy_factory != NULL) {
    unit_behavior_set_target_position(unit, unit->closest_enemy_factory->position, 120.0f);
    return 1;
  }
  return 0;
}

static int idle_movement(Unit * unit, Game * game) {
  unit_behavior_movement_stop(unit);
  return 1;
}

static void update_unit_behavior(Unit * unit, Game * game) {
  if (game->command_position_set) {
    unit->mode |= UNIT_MODE_FORCE_MOVE_TARGET_POSITION;
    unit->target_position = game->command_position;
  }

  move_inside_map(unit, game)
  || move_away_from_colliding_friendly_factory(unit, game)
  || move_away_from_colliding_friendly_unit(unit, game)
  || move_to_target_position(unit, game)
  || move_away_from_enemy_unit(unit, game)
  || move_to_enemy_unit(unit, game)
  || move_to_enemy_factory(unit, game)
  || idle_movement(unit, game);

  engage_enemy(unit, game);
}

static void update_entity_unit_behavior(Entity * entity, void * game_ptr) {
  if(entity->type == UNIT) {
    update_unit_behavior(&entity->unit, (Game *)game_ptr);
  }
}

static void mod_unit_behavior_update(Game * game, unsigned int delta, void * arg) {
  world_iterate_entities_of_type(&game->world, UNIT, game, update_entity_unit_behavior);
}

void mod_unit_behavior(GameModule * mod) {
  mod->update = mod_unit_behavior_update;
}
