#ifndef RENDERER_H
#define RENDERER_H

#include "vector3.h"
#include <SDL2/SDL.h>
#include "opengl.h"

typedef struct {
  SDL_Window * window;
  SDL_GLContext gl_context;
  int viewport_width;
  int viewport_height;
  Vector3 camera;
} Renderer;

#include "game.h"

#define PROJECTILE_LENGTH 16.0f
#define HALF_FACTORY_TEXTURE_SIZE 48
#define HALF_UNIT_TEXTURE_SIZE 24

void renderer_initialize(Renderer *);
void renderer_notify_viewport_resized(Renderer *);
Vector renderer_screen_to_world(Renderer *, Vector);
Vector renderer_world_to_screen(Renderer *, Vector);
void renderer_clear_color(Renderer *, float r, float g, float b);
void renderer_begin(Renderer *);
void renderer_render_map(Renderer *, Map *);
void renderer_render_world(Renderer *, World *);
void renderer_render_ui(Renderer *, Game *);
void renderer_align_ui(Renderer *, float x, float y, float scale);
void renderer_present(Renderer *);
void renderer_deinitialize(Renderer *);

void renderer_render_unit(Unit * unit);
void renderer_render_projectile(Projectile * projectile);
void renderer_render_factory(Factory * factory);

#endif
