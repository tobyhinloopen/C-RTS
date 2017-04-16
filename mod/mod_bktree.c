#include "mod_bktree.h"
#include "../bktree.h"
#include "../config.h"
#include <assert.h>

#ifdef CONFIG_BKTREE_ENABLED
#define MOD_BKTREE_CAPACITY 4096

static BKNode * nodes_buffer;
static int nodes_count[TEAM_COUNT];

static void mod_bktree_initialize(Game * game) {
  nodes_buffer = malloc(MOD_BKTREE_CAPACITY * sizeof(BKNode) * TEAM_COUNT);
  assert(nodes_buffer != NULL);
  for (int i = 0; i < TEAM_COUNT; i++)
    bktree_initialize(game->units_bktrees + i);
}

static void assign_unit_node(Entity * entity, void * nothing) {
  Unit unit = entity->unit;
  BKNode * nodes_buffer_for_team = nodes_buffer + MOD_BKTREE_CAPACITY * unit.team_id;
  BKNode * node = nodes_buffer_for_team + (nodes_count[unit.team_id]++);
  assert(nodes_count[unit.team_id] <= MOD_BKTREE_CAPACITY);
  node->x = BKTREE_TO_SCALAR(unit.position.x);
  node->y = BKTREE_TO_SCALAR(unit.position.y);
  node->value = (BKValue)entity;
}

static void mod_bktree_update(Game * game, unsigned int delta) {
  for (int i = 0; i < TEAM_COUNT; i++)
    nodes_count[i] = 0;
  world_iterate_entities_of_type(&game->world, UNIT, NULL, assign_unit_node);
  for (int i = 0; i < TEAM_COUNT; i++)
    bktree_build(game->units_bktrees + i, nodes_buffer + MOD_BKTREE_CAPACITY * i, nodes_count[i]);
}

static void mod_bktree_deinitialize(Game * game) {
  for (int i = 0; i < TEAM_COUNT; i++)
    bktree_deinitialize(game->units_bktrees + i);
}
#endif

void mod_bktree(GameModule * mod) {
#ifdef CONFIG_BKTREE_ENABLED
  mod->initialize = mod_bktree_initialize;
  mod->update = mod_bktree_update;
  mod->deinitialize = mod_bktree_deinitialize;
#endif
}
