#ifndef GUI_H
#define GUI_H

#include "gui/gui_component_group.h"

typedef struct {
  GUIComponentGroup root;
} GUI;

void gui_initialize(GUI * gui);
void gui_update(GUI * gui, unsigned int delta);
GUIComponent * gui_component_at(GUI * gui, int x, int y);
void gui_deinitialize(GUI * gui);

#endif
