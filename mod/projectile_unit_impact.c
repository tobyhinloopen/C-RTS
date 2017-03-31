#include "projectile_unit_impact.h"

#include "../world.h"
#include "../config.h"

#ifdef CONFIG_GRID_ENABLED
#include "../grid.h"
#endif

const float PROJECTILE_UNIT_IMPACT_DISTANCE = 12.0f;
const float PROJECTILE_FACTORY_IMPACT_DISTANCE = 24.0f;

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

#ifdef CONFIG_GRID_ENABLED
static void destroy_touching_entities(void * entity_ptr, void * projectile_ptr) {
  destroy_entity_touching_projectile((Entity *)entity_ptr, projectile_ptr);
}
#endif

static void destroy_entity_touching_projectile_entity(Entity * entity, void * game_ptr) {
  Projectile * projectile = &entity->projectile;
  if(entity->type == PROJECTILE && !projectile->hit_count) {
    Game * game = (Game *)game_ptr;

#ifdef CONFIG_GRID_ENABLED
    unsigned int x = 47.5f + projectile->position.x / 64;
    unsigned int y = 47.5f + projectile->position.y / 64;
    grid_iterate_items(&game->grid, (GridXY){ x, y }, projectile, destroy_touching_entities);
    grid_iterate_items(&game->grid, (GridXY){ x, y + 1 }, projectile, destroy_touching_entities);
    grid_iterate_items(&game->grid, (GridXY){ x + 1, y }, projectile, destroy_touching_entities);
    grid_iterate_items(&game->grid, (GridXY){ x + 1, y + 1 }, projectile, destroy_touching_entities);
#else
    world_iterate_entities(&game->world, projectile, destroy_entity_touching_projectile);
#endif

    if (projectile->hit_count)
      projectile->distance_remaining = 0;
  }
}

static void mod_projectile_unit_impact_update(Game * game, unsigned int delta) {
  world_iterate_entities(&game->world, game, destroy_entity_touching_projectile_entity);
}

void mod_projectile_unit_impact(GameModule * mod) {
  mod->update = mod_projectile_unit_impact_update;
}
