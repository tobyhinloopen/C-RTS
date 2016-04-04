#include <SDL2/SDL.h>
#include <assert.h>
#include "renderer.h"
#include "pi.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int HALF_UNIT_TEXTURE_SIZE = 32;
const int UNIT_TEXTURE_SIZE = HALF_UNIT_TEXTURE_SIZE*2;

SDL_Window * create_sdl_window();
SDL_Renderer * create_sdl_renderer(SDL_Window *);
void initialize_unit_texture(Renderer *);
void renderer_render_world_unit_callback(Unit *, void *);

void renderer_initialize(Renderer * renderer) {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  renderer->window = create_sdl_window();
  renderer->renderer = create_sdl_renderer(renderer->window);

  initialize_unit_texture(renderer);
}

void initialize_unit_texture(Renderer * renderer) {
  renderer->unit_texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE);
  SDL_SetTextureBlendMode(renderer->unit_texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer->renderer, renderer->unit_texture);
  renderer_clear_color(renderer, 255, 255, 255, 0);
  SDL_SetRenderDrawColor(renderer->renderer, 255, 0, 0, 255);
  SDL_Rect rect = { HALF_UNIT_TEXTURE_SIZE-12, HALF_UNIT_TEXTURE_SIZE-16, 24, 32 };
  SDL_RenderDrawRect(renderer->renderer, &rect);
  SDL_SetRenderTarget(renderer->renderer, NULL);
}

void renderer_clear_color(Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer->renderer, r, g, b, a);
  SDL_RenderClear(renderer->renderer);
}

void renderer_render_unit(Renderer * renderer, Unit * unit) {
  SDL_Rect dest_rect = {
    unit->position.x - HALF_UNIT_TEXTURE_SIZE + WINDOW_WIDTH/2,
    unit->position.y - HALF_UNIT_TEXTURE_SIZE + WINDOW_HEIGHT/2,
    UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE };
  SDL_RenderCopyEx(renderer->renderer, renderer->unit_texture, NULL, &dest_rect,
    unit->direction * RAD2DEGf, NULL, SDL_FLIP_NONE);
}

void renderer_render_world(Renderer * renderer, World * world) {
  world_iterate_units(world, renderer, renderer_render_world_unit_callback);
}

void renderer_render_world_unit_callback(Unit * unit, void * renderer) {
  renderer_render_unit((Renderer *)renderer, unit);
}

void renderer_present(Renderer * renderer) {
  SDL_RenderPresent(renderer->renderer);
}

void renderer_deinitialize(Renderer * renderer) {
  SDL_DestroyTexture(renderer->unit_texture);
  SDL_DestroyRenderer(renderer->renderer);
  SDL_DestroyWindow(renderer->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Window * create_sdl_window() {
  SDL_Window * sdl_window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  assert(sdl_window);
  return sdl_window;
}

SDL_Renderer * create_sdl_renderer(SDL_Window * window) {
  SDL_Renderer * sdl_renderer = SDL_CreateRenderer(window, -1, 0);
  assert(sdl_renderer);
  return sdl_renderer;
}
