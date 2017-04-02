#include "factory_spawn.h"
#include "../world.h"
#include "../team_id.h"
#include "../pi.h"

static void mod_factory_spawn_initialize(Game * game) {
  Map * map = &game->map;
  for (int i = 0; i < map->spawn_points_count; i++) {
    Vector spawn_point = map->spawn_points[i];
    Factory * factory = &world_entity_allocate(&game->world, FACTORY)->factory;
    factory_initialize(factory);
    factory->position = spawn_point;
    factory->team_id = TEAM_COLOR[i%TEAM_COUNT];
    factory->direction = PI + HALF_PI * TEAM_SPAWN[i%TEAM_COUNT].y;
    factory_start_building(factory);
  }
}

static void spawn_units_for_factory(Factory * factory, World * world) {
  Unit unit;
  while (factory_try_build_unit(factory, &unit))
    world_entity_allocate(world, UNIT)->unit = unit;
}

static void try_spawn_units_for_factory_entity(Entity * entity, void * world_ptr) {
  if (entity->type == FACTORY) {
    Factory * factory = &entity->factory;
    if (factory_is_building(factory)) {
      spawn_units_for_factory(factory, (World *)world_ptr);
      if (factory_health_percentage(factory) < 0.4) {
        factory_stop_building(factory);
      }
    } else if (factory_health_percentage(factory) > 0.8) {
      factory_start_building(factory);
    }
  }
}

static void mod_factory_spawn_update(Game * game, unsigned int delta) {
  world_iterate_entities(&game->world, &game->world, try_spawn_units_for_factory_entity);
}

void mod_factory_spawn(GameModule * mod) {
  mod->initialize = mod_factory_spawn_initialize;
  mod->update = mod_factory_spawn_update;
}