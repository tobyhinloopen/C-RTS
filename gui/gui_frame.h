#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "gui_string.h"

typedef struct _GUIComponent GUIComponent;

typedef struct {
  GUIString label;
  GUIComponent * root;
} GUIFrame;

#include "gui_component.h"

void gui_frame_initialize(GUIFrame *, const char * label);
void gui_frame_update(GUIFrame *, unsigned int);
void gui_frame_render(GUIFrame *);
void gui_frame_deinitialize(GUIFrame *);

#endif
