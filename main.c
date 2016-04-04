#include <stdio.h>
#include <time.h>
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

float randf() {
  return (float)((double)rand() / RAND_MAX);
}

void setup_unit(Unit * unit) {
  unit_initialize(unit);
  unit->throttle = .5f + .5f * randf();
  unit->position.x = -200.f + randf() * 400.f;
  unit->position.y = -200.f + randf() * 400.f;
  unit->direction = PI2f * -.5f + randf() * PI2f;
}

void render() {
  Renderer renderer;
  renderer_initialize(&renderer);

  World world;
  world_initialize(&world);

  srand(time(NULL));

  for(int i=0; i<1000; i++)
    setup_unit(&world_unit_allocate(&world)->unit);

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

    renderer_clear_color(&renderer, 255, 255, 255, 255);
    renderer_render_world(&renderer, &world);
    renderer_present(&renderer);

    last_time = current_time;
  }

  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&world);
  renderer_deinitialize(&renderer);
}
