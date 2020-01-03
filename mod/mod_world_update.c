#include "mod_world_update.h"
#include "../world.h"

void mod_world_update_update(Game * game, unsigned int delta_i, void * arg) {
  float delta = delta_i / 1000.f;
  if(delta > 0) {
    world_update(&game->world, delta);
  }
}

void mod_world_update(GameModule * mod) {
  mod->update = mod_world_update_update;
}
