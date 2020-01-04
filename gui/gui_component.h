#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

typedef struct _GUIComponent GUIComponent;

#include "gui_button.h"
#include "gui_component_group.h"
#include "gui_viewport.h"
#include "gui_frame.h"

#include "../util/rect.h"

typedef enum {
  GUI_COMPONENT_NONE = 0,
  GUI_COMPONENT_BUTTON = 1,
  GUI_COMPONENT_COMPONENT_GROUP,
  GUI_COMPONENT_FRAME,
  GUI_COMPONENT_VIEWPORT
} GUIComponentType;

struct _GUIComponent {
  GUIComponentType type;
  Rect rect;
  union {
    GUIButton button;
    GUIComponentGroup component_group;
    GUIFrame frame;
    GUIViewport viewport;
  };
};

void gui_component_initialize_button(GUIComponent *, const char * label);
void gui_component_initialize_viewport(GUIComponent *, void (*)(GUIViewport *, void * render_arg), void * render_arg);

void gui_component_update(GUIComponent *, unsigned int);
void gui_component_render(GUIComponent *);
void gui_component_deinitialize(GUIComponent *);

#endif
