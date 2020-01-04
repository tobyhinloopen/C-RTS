#ifndef GUI_STRING_H
#define GUI_STRING_H

typedef struct {
  const char * text;
  int length;
} GUIString;

void gui_string_initialize(GUIString *, const char *);
void gui_string_render(GUIString *);

#endif
