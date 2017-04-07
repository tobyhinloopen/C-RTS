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

static void print_world_pool_report(const char * type_label, WorldPool * world_pool) {
  unsigned int capacity = world_pool->entity_pool_count * WORLD_POOL_SIZE;
  printf("%12s - pools: %i - capacity: %i - entities: %i\n",
    type_label, world_pool->entity_pool_count, capacity, world_pool->entity_count);
}

static void print_world_report(World * world) {
  printf("\nPRINT PERFORMANCE - WORLD STATS\n");
  print_world_pool_report("units", &world->units);
  print_world_pool_report("factories", &world->factories);
  print_world_pool_report("projectiles", &world->projectiles);
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
