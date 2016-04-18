#ifndef RENDERER_H
#define RENDERER_H

#include "world.h"
#include "unit.h"
#include "vector.h"
#include "projectile.h"
#include <SDL2/SDL.h>

typedef struct {
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * unit_texture;
  SDL_Texture * unit_head_texture;
  int viewport_width;
  int viewport_height;
  float scale;
  Vector camera;
} Renderer;

void renderer_initialize(Renderer *);
void renderer_notify_viewport_resized(Renderer *);
Vector renderer_screen_to_world(Renderer *, Vector);
Vector renderer_world_to_screen(Renderer *, Vector);
void renderer_clear_color(Renderer *, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void renderer_render_world(Renderer *, World *);
void renderer_render_unit(Renderer *, Unit *);
void renderer_render_projectile(Renderer *, Projectile *);
void renderer_present(Renderer *);
void renderer_deinitialize(Renderer *);

#endif
