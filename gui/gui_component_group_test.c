#include "gui_component_group_test.h"
#include "gui_component_group.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void count_gui_component(GUIComponent * _component, void * count_ptr) {
  int * count = (int*)count_ptr;
  (*count)++;
}

void test_gui_component_group() {
  GUIComponentGroup group;
  gui_component_group_initialize(&group);

  GUIComponent component_a = {GUI_COMPONENT_BUTTON};
  gui_button_initialize(&component_a.button, "Foo");
  assert(strcmp(component_a.button.label.text, "Foo") == 0);
  gui_component_group_add(&group, &component_a);

  GUIComponent component_b = {GUI_COMPONENT_BUTTON};
  gui_button_initialize(&component_b.button, "Bar");
  assert(strcmp(component_b.button.label.text, "Bar") == 0);

  gui_component_group_add(&group, &component_b);

  int count = 0;
  gui_component_group_iterate(&group, count_gui_component, &count);
  assert(count == 2);
}
