#include "mod_projectile_unit_impact.h"

#include "../world.h"
#include "../config.h"

#ifdef CONFIG_SCALABLE_GRID_ENABLED
#include "../scalable_grid.h"
#endif

#define PROJECTILE_UNIT_IMPACT_DISTANCE 12.0f
#define PROJECTILE_FACTORY_IMPACT_DISTANCE 24.0f

#ifdef CONFIG_SCALABLE_GRID_ENABLED
#define PROJECTILE_MAX_IMPACT_DISTANCE PROJECTILE_FACTORY_IMPACT_DISTANCE

static void destroy_touching_entities(void * entity_ptr, float distance, void * projectile_ptr) {
  Entity * entity = (Entity *)entity_ptr;
  Unit * unit = &entity->unit;
  Factory * factory = &entity->factory;
  Projectile * projectile = (Projectile*)projectile_ptr;
  if (entity->type == UNIT) {
    if(unit->team_id != projectile->team_id && distance < PROJECTILE_UNIT_IMPACT_DISTANCE) {
      unit->health -= projectile_damage(projectile);
      projectile->hit_count++;
    }
  } else if(entity->type == FACTORY) {
    if(factory->team_id != projectile->team_id && distance < PROJECTILE_FACTORY_IMPACT_DISTANCE) {
      factory->health -= projectile_damage(projectile);
      if (factory_is_dead(factory)) {
        if (factory->team_id != NEUTRAL_TEAM_ID) {
          factory->health = FACTORY_INITIAL_HEALTH;
          factory->team_id = NEUTRAL_TEAM_ID;
        } else {
          factory->health = FACTORY_INITIAL_HEALTH * 0.1;
          factory->team_id = projectile->team_id;
        }
      }
      projectile->hit_count++;
    }
  }
}
#else
static void destroy_entity_touching_projectile(Entity * entity, void * projectile_ptr) {
  Unit * unit = &entity->unit;
  Factory * factory = &entity->factory;
  Projectile * projectile = (Projectile*)projectile_ptr;
  if(entity->type == UNIT
  && unit->team_id != projectile->team_id
  && vector_distance(projectile->position, unit->position) < PROJECTILE_UNIT_IMPACT_DISTANCE) {
    unit->health -= projectile_damage(projectile);
    projectile->hit_count++;
  } else if(entity->type == FACTORY
  && factory->team_id != projectile->team_id
  && vector_distance(projectile->position, factory->position) < PROJECTILE_FACTORY_IMPACT_DISTANCE) {
    factory->health -= projectile_damage(projectile);
    projectile->hit_count++;
  }
}

#endif

static void destroy_entity_touching_projectile_entity(Entity * entity, void * game_ptr) {
  Projectile * projectile = &entity->projectile;
  if(entity->type == PROJECTILE && !projectile->hit_count) {
    Game * game = (Game *)game_ptr;

#ifdef CONFIG_SCALABLE_GRID_ENABLED
  scalable_grid_iterate_items(&game->scalable_grid, projectile->position, PROJECTILE_MAX_IMPACT_DISTANCE, projectile, destroy_touching_entities);
#else
  world_iterate_entities_of_type(&game->world, UNIT, projectile, destroy_entity_touching_projectile);
  world_iterate_entities_of_type(&game->world, FACTORY, projectile, destroy_entity_touching_projectile);
#endif

    if (projectile->hit_count)
      projectile->distance_remaining = 0;
  }
}

static void mod_projectile_unit_impact_update(Game * game, unsigned int delta) {
  world_iterate_entities_of_type(&game->world, PROJECTILE, game, destroy_entity_touching_projectile_entity);
}

void mod_projectile_unit_impact(GameModule * mod) {
  mod->update = mod_projectile_unit_impact_update;
}
