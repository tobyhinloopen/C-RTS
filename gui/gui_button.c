#include "gui_button.h"

void gui_button_initialize(GUIButton * button, const char * label) {
  button->enabled = 1;
  gui_string_initialize(&button->label, label);
  gui_callback_clear(&button->onclick);
}

void gui_button_update(GUIButton * button, unsigned int delta) {
}

void gui_button_render(GUIButton * button) {
}

void gui_button_deinitialize(GUIButton * button) {
}
