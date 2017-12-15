#ifndef GUI_H
#define GUI_H

#include "gui/gui_component_group.h"
#include "vector.h"

typedef struct {
  GUIComponentGroup root;
} GUI;

void gui_initialize(GUI * gui);
void gui_update(GUI * gui, unsigned int delta);
void gui_render(GUI * gui);
GUIComponent * gui_component_at(GUI * gui, float x, float y);
void gui_deinitialize(GUI * gui);

#endif
