#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include "renderer.h"
#include "world.h"
#include "projectile.h"
#include "pi.h"

const float RAD2DEGf = 360 / PI2;

const int INITIAL_WINDOW_WIDTH = 640;
const int INITIAL_WINDOW_HEIGHT = 480;

const int HALF_UNIT_TEXTURE_SIZE = 24;
const int UNIT_TEXTURE_SIZE = HALF_UNIT_TEXTURE_SIZE*2;
const float PROJECTILE_LENGTH = 16.0f;
const float PROJECTILE_IMPACT_HALF_SIZE = 3.0f;
const int HEALTH_BAR_WIDTH = 32;
const int HEALTH_BAR_HEIGHT = 4;

typedef void (* RenderFunction)(SDL_Renderer *, SDL_Texture *);
typedef union { Uint32 color; struct { Uint8 b; Uint8 g; Uint8 r; }; } RendererColor;

static SDL_Window * create_sdl_window() {
  SDL_Window * sdl_window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI);
  assert(sdl_window);
  return sdl_window;
}

static SDL_Renderer * create_sdl_renderer(SDL_Window * window) {
  SDL_Renderer * sdl_renderer = SDL_CreateRenderer(window, -1, 0);
  assert(sdl_renderer);
  return sdl_renderer;
}

static void sdl_renderer_clear_color(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderClear(renderer);
}

static void initialize_texture(SDL_Renderer * renderer, SDL_Texture ** texture, RenderFunction render_fn) {
  *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE);
  SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer, *texture);
  sdl_renderer_clear_color(renderer, 255, 255, 255, 0);
  render_fn(renderer, *texture);
  SDL_SetRenderTarget(renderer, NULL);
}

static void render_unit_texture(SDL_Renderer * renderer, SDL_Texture * texture) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect rect = { HALF_UNIT_TEXTURE_SIZE-16, HALF_UNIT_TEXTURE_SIZE-12, 32, 24 };
  SDL_RenderDrawRect(renderer, &rect);
}

static void initialize_unit_texture(Renderer * renderer) {
  initialize_texture(renderer->renderer, &renderer->unit_texture, render_unit_texture);
}

static void render_unit_head_texture(SDL_Renderer * renderer, SDL_Texture * texture) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer,
    HALF_UNIT_TEXTURE_SIZE-4, HALF_UNIT_TEXTURE_SIZE-8,
    HALF_UNIT_TEXTURE_SIZE+4, HALF_UNIT_TEXTURE_SIZE);
  SDL_RenderDrawLine(renderer,
    HALF_UNIT_TEXTURE_SIZE-4, HALF_UNIT_TEXTURE_SIZE+8,
    HALF_UNIT_TEXTURE_SIZE+4, HALF_UNIT_TEXTURE_SIZE);
}

static void initialize_unit_head_texture(Renderer * renderer) {
  initialize_texture(renderer->renderer, &renderer->unit_head_texture, render_unit_head_texture);
}

void renderer_initialize(Renderer * renderer) {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  renderer->window = create_sdl_window();
  renderer->renderer = create_sdl_renderer(renderer->window);

  SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_BLEND);

  renderer_notify_viewport_resized(renderer);

  initialize_unit_texture(renderer);
  initialize_unit_head_texture(renderer);

  renderer->scale = 1.0f;
  vector_initialize(&renderer->camera);
}

void renderer_clear_color(Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  sdl_renderer_clear_color(renderer->renderer, r, g, b, a);
}

static void render_health_bar(Renderer * renderer, float x, float y, float health_percentage) {
  const int left_x = (int)x - HEALTH_BAR_WIDTH/2;
  const int top_y = (int)y - HEALTH_BAR_HEIGHT/2;

  SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
  const SDL_Rect outer_health_bar_rect = {
    left_x - 1, top_y - 1, HEALTH_BAR_WIDTH + 2, HEALTH_BAR_HEIGHT + 2 };
  SDL_RenderFillRect(renderer->renderer, &outer_health_bar_rect);

  if(health_percentage >= 0.6f)
    SDL_SetRenderDrawColor(renderer->renderer, 0, 255, 0, 255);
  else if(health_percentage >= 0.3f)
    SDL_SetRenderDrawColor(renderer->renderer, 255, 192, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer->renderer, 192, 0, 0, 255);

  const SDL_Rect inner_health_bar_rect = {
    left_x, top_y, HEALTH_BAR_WIDTH * health_percentage, HEALTH_BAR_HEIGHT };
  SDL_RenderFillRect(renderer->renderer, &inner_health_bar_rect);
}

void renderer_render_unit(Renderer * renderer, Unit * unit) {
  RendererColor color = { unit->team_id };
  SDL_SetTextureColorMod(renderer->unit_texture, color.r, color.g, color.b);
  SDL_SetTextureColorMod(renderer->unit_head_texture, color.r, color.g, color.b);

  Vector point = renderer_world_to_screen(renderer, unit->position);
  SDL_Rect dest_rect = { point.x - HALF_UNIT_TEXTURE_SIZE, point.y - HALF_UNIT_TEXTURE_SIZE,
    UNIT_TEXTURE_SIZE, UNIT_TEXTURE_SIZE };
  SDL_RenderCopyEx(renderer->renderer, renderer->unit_texture, NULL, &dest_rect,
    unit->direction * RAD2DEGf, NULL, SDL_FLIP_NONE);
  SDL_RenderCopyEx(renderer->renderer, renderer->unit_head_texture, NULL, &dest_rect,
    (unit->direction + unit->head_direction) * RAD2DEGf, NULL, SDL_FLIP_NONE);
}

void renderer_render_projectile(Renderer * renderer, Projectile * projectile) {
  RendererColor color = { projectile->team_id };
  SDL_SetRenderDrawColor(renderer->renderer, color.r, color.g, color.b,
    (Uint8)(projectile->decay_remaining / PROJECTILE_DECAY * 255.0f));
  Vector point = renderer_world_to_screen(renderer, projectile->position);
  if(projectile->distance_remaining > 0)
    SDL_RenderDrawLine(renderer->renderer, point.x, point.y,
      point.x + PROJECTILE_LENGTH * cosf(projectile->direction),
      point.y + PROJECTILE_LENGTH * sinf(projectile->direction));
  else {
    SDL_RenderDrawLine(renderer->renderer,
      point.x - PROJECTILE_IMPACT_HALF_SIZE, point.y - PROJECTILE_IMPACT_HALF_SIZE,
      point.x + PROJECTILE_IMPACT_HALF_SIZE, point.y + PROJECTILE_IMPACT_HALF_SIZE);
    SDL_RenderDrawLine(renderer->renderer,
      point.x + PROJECTILE_IMPACT_HALF_SIZE, point.y - PROJECTILE_IMPACT_HALF_SIZE,
      point.x - PROJECTILE_IMPACT_HALF_SIZE, point.y + PROJECTILE_IMPACT_HALF_SIZE);
  }
}

void renderer_notify_viewport_resized(Renderer * renderer) {
  SDL_GetRendererOutputSize(renderer->renderer,
    &renderer->viewport_width, &renderer->viewport_height);
}


Vector renderer_screen_to_world(Renderer * renderer, Vector point) {
  return (Vector) {
    (point.x - renderer->viewport_width/2) / renderer->scale + renderer->camera.x,
    (point.y - renderer->viewport_height/2) / renderer->scale + renderer->camera.y
  };
}

Vector renderer_world_to_screen(Renderer * renderer, Vector position) {
  return (Vector) {
    (position.x - renderer->camera.x) * renderer->scale + renderer->viewport_width/2,
    (position.y - renderer->camera.y) * renderer->scale + renderer->viewport_height/2
  };
}

static int is_vector_in_viewport(Renderer * renderer, Vector vector, int padding) {
  Vector point = renderer_world_to_screen(renderer, vector);
  return point.x + padding >= 0.0f && point.y + padding >= 0.0f
    && point.x - padding <= renderer->viewport_width
    && point.y - padding <= renderer->viewport_height;
}

static void render_entity_overlay(Entity * entity, void * renderer_ptr) {
  Renderer * renderer = (Renderer *)renderer_ptr;
  if(entity->type == UNIT
  && is_vector_in_viewport(renderer, entity->unit.position, HALF_UNIT_TEXTURE_SIZE)) {
    Unit * unit = &entity->unit;
    float health_percentage = unit_health_percentage(unit);
    if(health_percentage < 1.0f) {
      Vector point = renderer_world_to_screen(renderer, unit->position);
      point.y -= HALF_UNIT_TEXTURE_SIZE*renderer->scale;
      render_health_bar(renderer, point.x, point.y, health_percentage);
    }
  }
}

static void render_entity(Entity * entity, void * renderer_ptr) {
  Renderer * renderer = (Renderer *)renderer_ptr;
  switch(entity->type) {
    case UNIT:
      if(is_vector_in_viewport(renderer, entity->unit.position, HALF_UNIT_TEXTURE_SIZE))
        renderer_render_unit(renderer, &entity->unit);
      break;
    case PROJECTILE:
      if(is_vector_in_viewport(renderer, entity->projectile.position, PROJECTILE_LENGTH))
        renderer_render_projectile(renderer, &entity->projectile);
      break;
    case NONE: break;
  }
}

void renderer_render_world(Renderer * renderer, World * world) {
  //SDL_RenderSetScale(renderer->renderer, renderer->scale, renderer->scale);
  world_iterate_entities(world, renderer, render_entity);
  world_iterate_entities(world, renderer, render_entity_overlay);
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
