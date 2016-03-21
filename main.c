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
  Renderer renderer;
  renderer_initialize(&renderer);

  SDL_Renderer * sdl_renderer = SDL_CreateRenderer(renderer.window, -1, 0);
  if(!sdl_renderer)
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
  while(1) {
    SDL_Event event;
    if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;

    unsigned int current_time = SDL_GetTicks();
    float delta = (current_time - last_time) / 1000.0f;
    if(delta > 0)
      world_update(&world, delta);

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);

    SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
    SDL_Rect rect = { 0, 0, 24, 32 };

    int unit_index = 0;
    int world_unit_index = 0;
    while(unit_index < world.unit_count) {
      WorldUnit * world_unit = &world.units[world_unit_index++];
      if(world_unit->alive) {
        unit_index++;

        rect.x = world_unit->unit.position.x + 100;
        rect.y = world_unit->unit.position.y + 100;
        SDL_RenderDrawRect(sdl_renderer, &rect);
      }
    }


    SDL_RenderPresent(sdl_renderer);
    last_time = current_time;
  }
  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&world);
  SDL_DestroyRenderer(sdl_renderer);
  renderer_deinitialize(&renderer);
}
