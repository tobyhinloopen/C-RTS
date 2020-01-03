#include "mod_gui.h"
#include "../gui.h"
#include <assert.h>

static size_t mod_gui_alloc_size(Game * game) {
  return sizeof(GUIComponent);
}

static void mod_gui_initialize(Game * game, void * button_component_ptr) {
  gui_initialize(&game->gui);

  GUIComponent * button_component = button_component_ptr;
  gui_button_initialize(&button_component->button, "Foo");
  gui_component_group_add(&game->gui.root, button_component);
}

static void mod_gui_update(Game * game, unsigned int delta, void * button_component_ptr) {
  gui_update(&game->gui, delta);
}

static void mod_gui_deinitialize(Game * game, void * button_component_ptr) {
  gui_deinitialize(&game->gui);
}

void mod_gui(GameModule * mod) {
  mod->alloc_size = mod_gui_alloc_size;
  mod->initialize = mod_gui_initialize;
  mod->update = mod_gui_update;
  mod->deinitialize = mod_gui_deinitialize;
}
