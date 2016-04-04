#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "unit.h"
#include "renderer.h"
#include "test.h"
#include "world.h"
#include "pi.h"

void render();

int main(int argc, char **argv) {
  test();
  render();
  return 0;
}

void render() {
  Renderer rts_renderer;
  renderer_initialize(&rts_renderer);

  SDL_Renderer * renderer = SDL_CreateRenderer(rts_renderer.window, -1, 0);
  if(!renderer)
    printf("%s\n", SDL_GetError());

  World world;
  world_initialize(&world);

  WorldUnit * world_unit = world_unit_allocate(&world);
  unit_initialize(&world_unit->unit);
  world_unit->unit.throttle = 1.0f;
  world_unit->unit.direction = PI2f * -0.1f;

  SDL_InitSubSystem(SDL_INIT_TIMER);
  unsigned int start_time = SDL_GetTicks();
  unsigned int last_time = start_time;

  SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 64);
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_Rect rect = { 20, 16, 24, 32 };
  SDL_RenderDrawRect(renderer, &rect);
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  const double RAD2DEG = 360 / PI2f;

  while(1) {
    SDL_Event event;
    if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;

    unsigned int current_time = SDL_GetTicks();
    float delta = (current_time - last_time) / 1000.0f;
    if(delta > 0)
      world_update(&world, delta);

    SDL_RenderClear(renderer);

    int unit_index = 0;
    int world_unit_index = 0;
    while(unit_index < world.unit_count) {
      WorldUnit * world_unit = &world.units[world_unit_index++];
      if(world_unit->alive) {
        unit_index++;
        SDL_Rect dest_rect = { world_unit->unit.position.x - 32, world_unit->unit.position.y - 32, 64, 64 };
        SDL_RenderCopyEx(renderer, texture, NULL, &dest_rect, world_unit->unit.direction * RAD2DEG, NULL, SDL_FLIP_NONE);
      }
    }


    SDL_RenderPresent(renderer);
    last_time = current_time;
  }
  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&world);
  SDL_DestroyRenderer(renderer);
  renderer_deinitialize(&rts_renderer);
}
