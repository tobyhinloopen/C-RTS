#include "gui_component_group.h"
#include "gui_component.h"
#include <stdlib.h>
#include <assert.h>

#define GUI_COMPONENT_GROUP_INITIAL_CAPACITY 16

void gui_component_group_initialize(GUIComponentGroup * group) {
  linked_list_initialize(&group->items);
}

void gui_component_group_update(GUIComponentGroup * group, unsigned int delta) {
}

void gui_component_group_add(GUIComponent * group) {
}

GUIComponent * gui_component_group_component_at(GUIComponentGroup * group, int x, int y) {
  return NULL;
}

static int gui_component_group_deinitialization_iterator(void * gui_component_ptr, void * _) {
  GUIComponent * gui_component = (GUIComponent *)gui_component_ptr;
  gui_component_deinitialize(gui_component);
  return 0;
}

void gui_component_group_deinitialize(GUIComponentGroup * group) {
  linked_list_iterate(&group->items, gui_component_group_deinitialization_iterator, NULL);
  linked_list_deinitialize(&group->items);
}
