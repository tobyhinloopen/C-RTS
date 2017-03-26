#include "projectile_unit_impact.h"

#include "../world.h"

const float PROJECTILE_UNIT_IMPACT_DISTANCE = 12.0f;
const float PROJECTILE_FACTORY_IMPACT_DISTANCE = 24.0f;

static void destroy_entity_touching_projectile(Entity * entity, void * projectile_ptr) {
  Unit * unit = &entity->unit;
  Factory * factory = &entity->factory;
  Projectile * projectile = (Projectile*)projectile_ptr;
  if(entity->type == UNIT
  && unit->team_id != projectile->team_id
  && projectile->distance_remaining > 0
  && vector_distance(projectile->position, unit->position) < PROJECTILE_UNIT_IMPACT_DISTANCE) {
    unit->health -= projectile_damage(projectile);
    projectile->distance_remaining = 0;
  } else if(entity->type == FACTORY
  && factory->team_id != projectile->team_id
  && projectile->distance_remaining > 0
  && vector_distance(projectile->position, factory->position) < PROJECTILE_FACTORY_IMPACT_DISTANCE) {
    factory->health -= projectile_damage(projectile);
    projectile->distance_remaining = 0;
  }
}

static void destroy_entity_touching_projectile_entity(Entity * entity, void * world_ptr) {
  if(entity->type == PROJECTILE) {
    world_iterate_entities((World*)world_ptr, &entity->projectile, destroy_entity_touching_projectile);
  }
}

static void mod_projectile_unit_impact_update(Game * game, unsigned int delta) {
  world_iterate_entities(&game->world, &game->world, destroy_entity_touching_projectile_entity);
}

void mod_projectile_unit_impact(GameModule * mod) {
  mod->update = mod_projectile_unit_impact_update;
}
