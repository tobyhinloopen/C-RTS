#include "gui_viewport.h"

void gui_viewport_initialize(GUIViewport * viewport, void (* render_func)(GUIViewport *, void *), void * render_arg) {
  viewport->x = 0;
  viewport->y = 0;
  viewport->width = 0;
  viewport->height = 0;
  viewport->center_x = 0;
  viewport->center_y = 0;
  viewport->zoom = 1;
  viewport->render_func = render_func;
  viewport->render_arg = render_arg;
}

void gui_viewport_update(GUIViewport * viewport, unsigned int delta) {
}

void gui_viewport_render(const GUIViewport * viewport) {
  viewport->render_func(viewport, viewport->render_arg);
}

float gui_viewport_scale(const GUIViewport * viewport) {
  return 1.0f / (1.0f + viewport->zoom);
}

Vector gui_viewport_screen_to_world(const GUIViewport * viewport, Vector point) {
  const float scale = gui_viewport_scale(viewport);
  return (Vector) {
    (point.x - viewport->width/2) / scale + viewport->center_x,
    (point.y - viewport->height/2) / -scale + viewport->center_y
  };
}

Vector gui_viewport_world_to_screen(const GUIViewport * viewport, Vector position) {
  const float scale = gui_viewport_scale(viewport);
  return (Vector) {
    (position.x - viewport->center_x) * scale + viewport->width/2,
    (position.y - viewport->center_y) * -scale + viewport->height/2
  };
}

int gui_viewport_contains_world_position(const GUIViewport * viewport, Vector position, float padding) {
  Vector point = gui_viewport_world_to_screen(viewport, position);
  return point.x + padding >= 0.0f
    && point.y + padding >= 0.0f
    && point.x - padding <= viewport->width
    && point.y - padding <= viewport->height;
}

void gui_viewport_deinitialize(GUIViewport * viewport) {
}
