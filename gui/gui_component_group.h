#ifndef GUI_COMPONENT_GROUP_H
#define GUI_COMPONENT_GROUP_H

#include "../util/linked_list.h"

typedef struct {
  LinkedList items;
} GUIComponentGroup;

#include "gui_component.h"

void gui_component_group_initialize(GUIComponentGroup *);
void gui_component_group_update(GUIComponentGroup *, unsigned int delta);
void gui_component_group_add(GUIComponent *);
GUIComponent * gui_component_group_component_at(GUIComponentGroup *, int x, int y);
void gui_component_group_deinitialize(GUIComponentGroup *);

#endif
