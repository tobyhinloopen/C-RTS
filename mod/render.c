#include "render.h"

#include "../renderer.h"
#include "../camera.h"

static void mod_render_initialize(Game * game) {
  renderer_initialize(&game->renderer);
}

static void mod_render_tick(Game * game) {
}

static void handle_window_resize(Game * game) {
  if(game->is_window_resized) {
    renderer_notify_viewport_resized(&game->renderer);
    game->is_window_resized = 0;
  }
}

static void mod_render_update(Game * game, unsigned int delta_i) {
  float delta = delta_i / 1000.f;
  if(delta > 0) {
    camera_update(&game->renderer.camera, game->camera_movement, delta);
    world_update(&game->world, delta);
  }

  handle_window_resize(game);
  renderer_clear_color(&game->renderer, 1.0f, 1.0f, 1.0f);
  renderer_render_world(&game->renderer, &game->world);
  renderer_present(&game->renderer);
}

static void mod_render_deinitialize(Game * game) {
  renderer_deinitialize(&game->renderer);
}

void mod_render(GameModule * mod) {
  mod->initialize = mod_render_initialize;
  mod->tick = mod_render_tick;
  mod->update = mod_render_update;
  mod->deinitialize = mod_render_deinitialize;
}
