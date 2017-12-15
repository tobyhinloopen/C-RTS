#ifndef GUI_VIEWPORT_H
#define GUI_VIEWPORT_H

#include "../vector.h"

typedef struct _GUIViewport GUIViewport;

struct _GUIViewport {
  int x;
  int y;
  int width;
  int height;
  int center_x;
  int center_y;
  int zoom;
  void (* render_func)(GUIViewport *, void * arg);
  void * render_arg;
};

void gui_viewport_initialize(GUIViewport *, void (*)(GUIViewport *, void * render_arg), void * render_arg);
void gui_viewport_update(GUIViewport *, unsigned int);
void gui_viewport_render(const GUIViewport *);
float gui_viewport_scale(const GUIViewport *);
Vector gui_viewport_screen_to_world(const GUIViewport *, Vector);
Vector gui_viewport_world_to_screen(const GUIViewport *, Vector);
int gui_viewport_contains_world_position(const GUIViewport *, Vector, float);
void gui_viewport_deinitialize(GUIViewport *);

#endif
