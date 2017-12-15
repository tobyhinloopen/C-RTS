#include "gui_callback.h"

void gui_callback_clear(GUICallback * callback) {
  callback->func = (void *)0;
  callback->arg = (void *)0;
}
