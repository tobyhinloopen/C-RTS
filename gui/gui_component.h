#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

typedef struct _GUIComponent GUIComponent;

#include "gui_button.h"
#include "gui_component_group.h"
#include "gui_viewport.h"
#include "gui_frame.h"

typedef enum {BUTTON, COMPONENT_GROUP, FRAME, VIEWPORT} GUIComponentType;

struct _GUIComponent {
  GUIComponentType type;
  union {
    GUIButton button;
    GUIComponentGroup component_group;
    GUIFrame frame;
    GUIViewport viewport;
  };
};

void gui_component_update(GUIComponent *, unsigned int);
void gui_component_deinitialize(GUIComponent *);

#endif
