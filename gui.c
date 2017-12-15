#include "gui.h"

void gui_initialize(GUI * gui) {
  gui_component_group_initialize(&gui->root);
}

void gui_update(GUI * gui, unsigned int delta) {
  gui_component_group_update(&gui->root, delta);
}

void gui_render(GUI * gui) {
  gui_component_group_render(&gui->root);
}

GUIComponent * gui_component_at(GUI * gui, float x, float y) {
  return gui_component_group_component_at(&gui->root, x, y);
}

void gui_deinitialize(GUI * gui) {
  gui_component_group_deinitialize(&gui->root);
}
