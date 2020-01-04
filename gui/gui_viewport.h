#ifndef GUI_VIEWPORT_H
#define GUI_VIEWPORT_H

#include "../vector.h"

typedef struct _GUIViewport GUIViewport;

struct _GUIViewport {
  int x; // deprecated
  int y; // deprecated
  int width; // deprecated
  int height; // deprecated
  int center_x;
  int center_y;
  int zoom;
  void (* render_func)(GUIViewport *, void * arg);
  void * render_arg;
};

void gui_viewport_initialize(GUIViewport *, void (*)(GUIViewport *, void * render_arg), void * render_arg);
void gui_viewport_update(GUIViewport *, unsigned int);
void gui_viewport_render(GUIViewport *);
float gui_viewport_scale(GUIViewport *);
Vector gui_viewport_screen_to_world(GUIViewport *, Vector);
Vector gui_viewport_world_to_screen(GUIViewport *, Vector);
int gui_viewport_contains_world_position(GUIViewport *, Vector, float);
void gui_viewport_deinitialize(GUIViewport *);

#endif
