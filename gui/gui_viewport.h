#ifndef GUI_VIEWPORT_H
#define GUI_VIEWPORT_H

typedef struct {
  int center_x;
  int center_y;
  int zoom;
} GUIViewport;

void gui_viewport_update(GUIViewport *, unsigned int);
void gui_viewport_deinitialize(GUIViewport *);

#endif
