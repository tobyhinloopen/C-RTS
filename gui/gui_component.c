#include "gui_component.h"

void gui_component_update(GUIComponent * gui_component, unsigned int delta) {
  switch(gui_component->type) {
    case BUTTON:
      gui_button_update(&gui_component->button, delta);
      break;
    case COMPONENT_GROUP:
      gui_component_group_update(&gui_component->component_group, delta);
      break;
    case FRAME:
      gui_frame_update(&gui_component->frame, delta);
      break;
    case VIEWPORT:
      gui_viewport_update(&gui_component->viewport, delta);
      break;
  }
}

void gui_component_deinitialize(GUIComponent * gui_component) {
  switch(gui_component->type) {
    case BUTTON:
      gui_button_deinitialize(&gui_component->button);
      break;
    case COMPONENT_GROUP:
      gui_component_group_deinitialize(&gui_component->component_group);
      break;
    case FRAME:
      gui_frame_deinitialize(&gui_component->frame);
      break;
    case VIEWPORT:
      gui_viewport_deinitialize(&gui_component->viewport);
      break;
  }
}
