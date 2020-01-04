#include "mod_gui.h"
#include "../gui_impl/game_viewport.h"
#include "../gui.h"
#include <assert.h>

typedef struct {
  GUIComponent viewport;
  GUIComponent sample_button;
  GameViewport game_viewport;
} ModGui;

static size_t mod_gui_alloc_size(Game * game) {
  return sizeof(ModGui);
}

static void mod_gui_initialize(Game * game, void * mod_gui_ptr) {
  gui_initialize(&game->gui);

  ModGui * mod_gui = mod_gui_ptr;
  gui_component_initialize_viewport(&mod_gui->viewport, NULL, NULL);

  GUIViewport * viewport = &mod_gui->viewport.viewport;
  game_viewport_initialize(&mod_gui->game_viewport, game, viewport);

  gui_component_initialize_button(&mod_gui->sample_button, "Foo");
  // gui_component_group_add(&game->gui.root, &mod_gui->viewport);
  // gui_component_group_add(&game->gui.root, &mod_gui->sample_button);
}

static void mod_gui_update(Game * game, unsigned int delta, void * mod_gui_ptr) {
  gui_update(&game->gui, delta);
}

static void mod_gui_deinitialize(Game * game, void * mod_gui_ptr) {
  gui_deinitialize(&game->gui);
}

void mod_gui(GameModule * mod) {
  mod->alloc_size = mod_gui_alloc_size;
  mod->initialize = mod_gui_initialize;
  mod->update = mod_gui_update;
  mod->deinitialize = mod_gui_deinitialize;
}
