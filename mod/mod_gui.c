#include "mod_gui.h"
#include "../gui.h"

static void mod_gui_initialize(Game * game) {
  gui_initialize(&game->gui);
}

static void mod_gui_update(Game * game, unsigned int delta) {
  gui_update(&game->gui, delta);
}

static void mod_gui_deinitialize(Game * game) {
  gui_deinitialize(&game->gui);
}

void mod_gui(GameModule * mod) {
  mod->initialize = mod_gui_initialize;
  mod->update = mod_gui_update;
  mod->deinitialize = mod_gui_deinitialize;
}
