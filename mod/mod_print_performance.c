#include "mod_print_performance.h"
#include <stdio.h>
#include <time.h>


static void print_performance(GameModule * mod, clock_t duration) {
  printf("%s %luC\n", mod->name, duration);
}

static void mod_print_performance_initialize(Game * game) {
  printf("\nPRINT PERFORMANCE - INITIALIZE\n");
  for (int i = 0; i < game->modules_count; i++) {
    GameModule * mod = &game->modules[i];
    print_performance(mod, mod->duration_initialize);
  }
}

static clock_t duration_avg(clock_t * durations, int duration_count) {
  clock_t sum = 0;
  for (int i = 0; i < duration_count; i++)
    sum += durations[i];
  return sum / duration_count;
}

typedef struct {
  int unit_count;
  int projectile_count;
  int factory_count;
} WorldEntityCountResult;

static void increase_entity_count(Entity * entity, void * result_ptr) {
  WorldEntityCountResult * result = (WorldEntityCountResult *)result_ptr;
  switch(entity->type) {
    case UNIT: result->unit_count++; break;
    case PROJECTILE: result->projectile_count++; break;
    case FACTORY: result->factory_count++; break;
    case NONE:
    default:
      break;
  }
}

static WorldEntityCountResult world_count_entities(World * world) {
  WorldEntityCountResult result = {0, 0, 0};
  world_iterate_entities(world, &result, increase_entity_count);
  return result;
}

static void print_world_report(World * world) {
  printf("\nPRINT PERFORMANCE - WORLD STATS\n");

  int capacity = world->entity_pool_count * WORLD_POOL_SIZE;
  printf("Pools: %i\nPool Size: %i\nEntity capacity: %i\n",
    world->entity_pool_count, WORLD_POOL_SIZE, capacity);

  WorldEntityCountResult result = world_count_entities(world);
  int entity_count = result.unit_count + result.projectile_count + result.factory_count;
  printf("Entities: %i (%2.1f%%)\nUnits: %i\nProjectiles: %i\nFactories %i\n",
    entity_count, (100.0 * entity_count / capacity), result.unit_count, result.projectile_count, result.factory_count);
}

static void mod_print_performance_update(Game * game, unsigned int delta) {
  if (game->modules->duration_update_index == 0 && delta > 0) {
    printf("\nPRINT PERFORMANCE - UPDATE\n");
    for (int i = 0; i < game->modules_count; i++) {
      GameModule * mod = &game->modules[i];
      print_performance(mod, duration_avg(mod->duration_update, GAME_MODULE_DURATION_LENGTH));
    }

    print_world_report(&game->world);
  }
}

static void mod_print_performance_deinitialize(Game * game) {
  printf("\nPRINT PERFORMANCE - DEINITIALIZE\n");
  for (int i = 0; i < game->modules_count; i++) {
    GameModule * mod = &game->modules[i];
    print_performance(mod, mod->duration_deinitialize);
  }
}

void mod_print_performance(GameModule * mod) {
  mod->initialize = mod_print_performance_initialize;
  mod->update = mod_print_performance_update;
  mod->deinitialize = mod_print_performance_deinitialize;
}
