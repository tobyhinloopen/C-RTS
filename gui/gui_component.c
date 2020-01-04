#include "gui_component.h"

void gui_component_initialize_button(GUIComponent * gui_component, const char * label) {
  gui_component->type = GUI_COMPONENT_BUTTON;
  gui_button_initialize(&gui_component->button, label);
}

void gui_component_initialize_viewport(
  GUIComponent * gui_component,
  void (* render_fn)(GUIViewport *, void * render_arg),
  void * render_arg
) {
  gui_component->type = GUI_COMPONENT_VIEWPORT;
  gui_viewport_initialize(&gui_component->viewport, render_fn, render_arg);
}

void gui_component_update(GUIComponent * gui_component, unsigned int delta) {
  switch(gui_component->type) {
    case GUI_COMPONENT_BUTTON:
      gui_button_update(&gui_component->button, delta);
      break;
    case GUI_COMPONENT_COMPONENT_GROUP:
      gui_component_group_update(&gui_component->component_group, delta);
      break;
    case GUI_COMPONENT_FRAME:
      gui_frame_update(&gui_component->frame, delta);
      break;
    case GUI_COMPONENT_VIEWPORT:
      gui_viewport_update(&gui_component->viewport, delta);
      break;
    case GUI_COMPONENT_NONE: break;
  }
}

void gui_component_render(GUIComponent * gui_component) {
  switch(gui_component->type) {
    case GUI_COMPONENT_BUTTON:
      gui_button_render(&gui_component->button);
      break;
    case GUI_COMPONENT_COMPONENT_GROUP:
      gui_component_group_render(&gui_component->component_group);
      break;
    case GUI_COMPONENT_FRAME:
      gui_frame_render(&gui_component->frame);
      break;
    case GUI_COMPONENT_VIEWPORT:
      gui_viewport_render(&gui_component->viewport);
      break;
    case GUI_COMPONENT_NONE: break;
  }
}

void gui_component_deinitialize(GUIComponent * gui_component) {
  switch(gui_component->type) {
    case GUI_COMPONENT_BUTTON:
      gui_button_deinitialize(&gui_component->button);
      break;
    case GUI_COMPONENT_COMPONENT_GROUP:
      gui_component_group_deinitialize(&gui_component->component_group);
      break;
    case GUI_COMPONENT_FRAME:
      gui_frame_deinitialize(&gui_component->frame);
      break;
    case GUI_COMPONENT_VIEWPORT:
      gui_viewport_deinitialize(&gui_component->viewport);
      break;
    case GUI_COMPONENT_NONE: break;
  }
  gui_component->type = GUI_COMPONENT_NONE;
}
