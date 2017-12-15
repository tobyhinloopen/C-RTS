#ifndef GUI_COMPONENT_GROUP_H
#define GUI_COMPONENT_GROUP_H

#include "../util/linked_list.h"

typedef struct {
  LinkedList items;
} GUIComponentGroup;

#include "gui_component.h"

void gui_component_group_initialize(GUIComponentGroup *);
void gui_component_group_update(GUIComponentGroup *, unsigned int delta);
void gui_component_group_add(GUIComponentGroup *, GUIComponent *);
void gui_component_group_iterate(GUIComponentGroup *, void (*)(GUIComponent *, void *), void *);
void gui_component_group_render(GUIComponentGroup *);
GUIComponent * gui_component_group_component_at(GUIComponentGroup *, float x, float y);
void gui_component_group_deinitialize(GUIComponentGroup *);

#endif
