#include "mod_camera_update.h"
#include "../camera.h"

void mod_camera_update_update(Game * game, unsigned int delta_i, void * arg) {
  float delta = delta_i / 1000.f;
  if(delta > 0) {
    camera_update(&game->renderer.camera, game->camera_movement, delta);
  }
}

void mod_camera_update(GameModule * mod) {
  mod->update = mod_camera_update_update;
}
