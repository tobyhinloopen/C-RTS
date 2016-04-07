#include <SDL2/SDL.h>
#include <assert.h>
#include "renderer.h"
#include "pi.h"

const float RAD2DEGf = 360 / PI2;

const int INITIAL_WINDOW_WIDTH = 640;
const int INITIAL_WINDOW_HEIGHT = 480;

const int HALF_UNIT_TEXTURE_SIZE = 32;
const int UNIT_TEXTURE_SIZE = HALF_UNIT_TEXTURE_SIZE*2;

typedef void (* RenderFunction)(SDL_Renderer *, SDL_Texture *);
typedef union { Uint32 color; struct { Uint8 b; Uint8 g; Uint8 r; }; } RendererColor;

SDL_Window * create_sdl_window();
SDL_Renderer * create_sdl_renderer(SDL_Window *);
void initialize_texture(SDL_Renderer *, SDL_Texture **, RenderFunction);
void render_unit_texture(SDL_Renderer * renderer, SDL_Texture * texture);
void render_unit_head_texture(SDL_Renderer * renderer, SDL_Texture * texture);
void initialize_unit_texture(Renderer *);
void initialize_unit_head_texture(Renderer *);
void renderer_render_world_unit_callback(Unit *, void *);
void sdl_renderer_clear_color(SDL_Renderer *, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void renderer_initialize(Renderer * renderer) {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  renderer->window = create_sdl_window();
  renderer->renderer = create_sdl_renderer(renderer->window);

  renderer_notify_viewport_resized(renderer);

  initialize_unit_texture(renderer);
  initialize_unit_head_texture(renderer);
}

void initialize_unit_texture(Renderer * renderer) {
  initialize_texture(renderer->renderer, &renderer->unit_texture, render_unit_texture);
}

void initialize_unit_head_texture(Renderer * renderer) {
  initialize_texture(renderer->renderer, &renderer->unit_head_texture, render_unit_head_texture);
}

void initialize_texture(SDL_Renderer * renderer, SDL_Texture ** texture, RenderFunction render_fn) {
  *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE);
  SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer, *texture);
  sdl_renderer_clear_color(renderer, 255, 255, 255, 0);
  render_fn(renderer, *texture);
  SDL_SetRenderTarget(renderer, NULL);
}

void render_unit_texture(SDL_Renderer * renderer, SDL_Texture * texture) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect = { HALF_UNIT_TEXTURE_SIZE-12, HALF_UNIT_TEXTURE_SIZE-16, 24, 32 };
  SDL_RenderDrawRect(renderer, &rect);
}

void render_unit_head_texture(SDL_Renderer * renderer, SDL_Texture * texture) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer,
    HALF_UNIT_TEXTURE_SIZE, HALF_UNIT_TEXTURE_SIZE+4,
    HALF_UNIT_TEXTURE_SIZE-8, HALF_UNIT_TEXTURE_SIZE-4);
  SDL_RenderDrawLine(renderer,
    HALF_UNIT_TEXTURE_SIZE, HALF_UNIT_TEXTURE_SIZE+4,
    HALF_UNIT_TEXTURE_SIZE+8, HALF_UNIT_TEXTURE_SIZE-4);
}

void renderer_clear_color(Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  sdl_renderer_clear_color(renderer->renderer, r, g, b, a);
}

void sdl_renderer_clear_color(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderClear(renderer);
}

void renderer_render_unit(Renderer * renderer, Unit * unit) {
  RendererColor color = { unit->team_id };
  SDL_SetTextureColorMod(renderer->unit_texture, color.r, color.g, color.b);
  SDL_SetTextureColorMod(renderer->unit_head_texture, color.r, color.g, color.b);

  SDL_Rect dest_rect = {
    unit->position.x - HALF_UNIT_TEXTURE_SIZE + renderer->viewport_width/2,
    unit->position.y - HALF_UNIT_TEXTURE_SIZE + renderer->viewport_height/2,
    UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE };
  SDL_RenderCopyEx(renderer->renderer, renderer->unit_texture, NULL, &dest_rect,
    unit->direction * RAD2DEGf, NULL, SDL_FLIP_NONE);
  SDL_RenderCopyEx(renderer->renderer, renderer->unit_head_texture, NULL, &dest_rect,
    (unit->direction + unit->head_direction) * RAD2DEGf, NULL, SDL_FLIP_NONE);
}

void renderer_notify_viewport_resized(Renderer * renderer) {
  SDL_GetWindowSize(renderer->window, &renderer->viewport_width, &renderer->viewport_height);
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
  SDL_DestroyTexture(renderer->unit_head_texture);
  SDL_DestroyTexture(renderer->unit_texture);
  SDL_DestroyRenderer(renderer->renderer);
  SDL_DestroyWindow(renderer->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_Window * create_sdl_window() {
  SDL_Window * sdl_window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  assert(sdl_window);
  return sdl_window;
}

SDL_Renderer * create_sdl_renderer(SDL_Window * window) {
  SDL_Renderer * sdl_renderer = SDL_CreateRenderer(window, -1, 0);
  assert(sdl_renderer);
  return sdl_renderer;
}
