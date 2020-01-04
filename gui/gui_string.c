#include "gui_string.h"
#include "../text_renderer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void gui_string_initialize(GUIString * str, const char * text) {
  assert(text);
  str->length = strlen(text);
  str->text = text;
}

void gui_string_render(GUIString * str) {
  text_renderer_render_string(str->text, str->length);
}
