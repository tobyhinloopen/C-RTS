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

void gui_component_group_add(GUIComponentGroup * group, GUIComponent * component) {
  linked_list_push_front(&group->items, component);
}

GUIComponent * gui_component_group_component_at(GUIComponentGroup * group, float x, float y) {
  return NULL;
}

typedef struct {
  void (* func)(GUIComponent *, void *);
  void * arg;
} GUIComponentGroupIteratorContext;

static int gui_component_group_iterator(void * gui_component_ptr, void * context_ptr) {
  GUIComponentGroupIteratorContext * ctx = (GUIComponentGroupIteratorContext *)context_ptr;
  ctx->func((GUIComponent *)gui_component_ptr, ctx->arg);
  return 0;
}

void gui_component_group_iterate(GUIComponentGroup * group, void (* func)(GUIComponent *, void *), void * arg) {
  GUIComponentGroupIteratorContext ctx = {func, arg};
  linked_list_iterate(&group->items, gui_component_group_iterator, &ctx);
}

static void render_gui_component_iterator(GUIComponent * gui_component, void * _) {
  gui_component_render(gui_component);
}

void gui_component_group_render(GUIComponentGroup * group) {
  gui_component_group_iterate(group, render_gui_component_iterator, NULL);
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
