#include "gui_frame.h"

void gui_frame_initialize(GUIFrame * frame, const char * label) {
  gui_string_initialize(&frame->label, label);
  frame->root = (void *)0;
}

void gui_frame_update(GUIFrame * frame, unsigned int delta) {
}

void gui_frame_render(GUIFrame * button) {
}

void gui_frame_deinitialize(GUIFrame * frame) {
}
