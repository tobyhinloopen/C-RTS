#include "gui_string.h"
#include <assert.h>
#include <string.h>

void gui_string_initialize(GUIString * str, const char * text) {
  assert(text);
  str->length = strlen(text);
  str->text = text;
}
