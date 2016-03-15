#include <SDL2/SDL.h>
#include <assert.h>
#include "renderer.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window * create_sdl_window();

void renderer_initialize(Renderer *renderer) {
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  renderer->window = create_sdl_window();
  renderer->surface = SDL_GetWindowSurface(renderer->window);
}

void renderer_deinitialize(Renderer *renderer) {
  SDL_DestroyWindow(renderer->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Window * create_sdl_window() {
  SDL_Window * window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  assert(window != NULL);
  return window;
}
