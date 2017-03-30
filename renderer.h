#ifndef RENDERER_H
#define RENDERER_H

#include "world.h"
#include "unit.h"
#include "vector3.h"
#include "projectile.h"
#include <SDL2/SDL.h>
#include "opengl.h"

typedef struct {
  SDL_Window * window;
  SDL_GLContext gl_context;
  int viewport_width;
  int viewport_height;
  Vector3 camera;
} Renderer;

void renderer_initialize(Renderer *);
void renderer_notify_viewport_resized(Renderer *);
Vector renderer_screen_to_world(Renderer *, Vector);
Vector renderer_world_to_screen(Renderer *, Vector);
void renderer_clear_color(Renderer *, float r, float g, float b);
void renderer_render_world(Renderer *, World *);
void renderer_present(Renderer *);
void renderer_deinitialize(Renderer *);

#endif
