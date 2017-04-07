#include "mod_unit_projectile_spawn.h"
#include "../rand_range.h"

static Projectile * create_unit_projectile(Unit * unit, World * world, rand_range_seed_t * seed) {
  Projectile * projectile = &world_entity_allocate(world, PROJECTILE)->projectile;
  projectile_initialize(projectile, unit->position,
    unit->direction + unit->head_direction + rand_rangef(seed, -0.02f, 0.02f), unit->team_id);
  projectile->distance_remaining *= rand_rangef(seed, 0.9f, 1.1f);
  return projectile;
}

static void create_unit_projectiles(Unit * unit, World * world, rand_range_seed_t * seed) {
  if(unit_is_firing(unit)) {
    while(unit->next_fire_interval < 0) {
      Projectile * projectile = create_unit_projectile(unit, world, seed);
      projectile_update(projectile, -unit->next_fire_interval);
      unit->next_fire_interval += UNIT_FIRE_INTERVAL;
    }
  }
}

static void create_unit_entity_projectiles(Entity * entity, void * game_ptr) {
  Game * game = (Game *)game_ptr;
  create_unit_projectiles(&entity->unit, &game->world, &game->seed);
}

static void mod_unit_projectile_spawn_update(Game * game, unsigned int delta) {
  world_iterate_entities_of_type(&game->world, UNIT, game, create_unit_entity_projectiles);
}

void mod_unit_projectile_spawn(GameModule * mod) {
  mod->update = mod_unit_projectile_spawn_update;
}
