#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "gui_string.h"

typedef struct _GUIComponent GUIComponent;

typedef struct {
  GUIString label;
  GUIComponent * root;
} GUIFrame;

#include "gui_component.h"

void gui_frame_update(GUIFrame *, unsigned int);
void gui_frame_deinitialize(GUIFrame *);

#endif
