#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "gui_string.h"
#include "gui_callback.h"

typedef struct {
  int enabled;
  GUIString label;
  GUICallback onclick;
} GUIButton;

#include "gui_component.h"

void gui_button_initialize(GUIButton *, const char *);
void gui_button_update(GUIButton *, unsigned int);
void gui_button_render(GUIButton *);
void gui_button_deinitialize(GUIButton *);

#endif
