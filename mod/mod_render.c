#include "mod_render.h"

#include "../renderer.h"
#include "../camera.h"

static void mod_render_initialize(Game * game, void * arg) {
  renderer_initialize(&game->renderer);
}

static void handle_window_resize(Game * game) {
  if(game->is_window_resized) {
    renderer_notify_viewport_resized(&game->renderer);
    game->is_window_resized = 0;
  }
}

static void mod_render_update(Game * game, unsigned int delta_i, void * arg) {
  handle_window_resize(game);
  renderer_begin(&game->renderer);
  renderer_render_map(&game->renderer, &game->map);
  renderer_render_world(&game->renderer, &game->world);
  renderer_render_ui(&game->renderer, game);
  renderer_present(&game->renderer);
}

static void mod_render_deinitialize(Game * game, void * arg) {
  renderer_deinitialize(&game->renderer);
}

void mod_render(GameModule * mod) {
  mod->initialize = mod_render_initialize;
  mod->update = mod_render_update;
  mod->deinitialize = mod_render_deinitialize;
}
