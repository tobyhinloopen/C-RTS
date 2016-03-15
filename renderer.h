#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

typedef struct {
  SDL_Window* window;
  SDL_Surface* surface;
} Renderer;

void renderer_initialize(Renderer *renderer);
void renderer_deinitialize(Renderer *renderer);

#endif
