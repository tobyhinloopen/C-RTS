#ifndef RENDERER_H
#define RENDERER_H

#include "world.h"
#include "unit.h"
#include <SDL2/SDL.h>

typedef struct {
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * unit_texture;
} Renderer;

void renderer_initialize(Renderer * renderer);
void renderer_clear_color(Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void renderer_render_world(Renderer * renderer, World * world);
void renderer_render_unit(Renderer * renderer, Unit * unit);
void renderer_present(Renderer * renderer);
void renderer_deinitialize(Renderer * renderer);

#endif
