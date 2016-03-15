#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "unit.h"
#include "renderer.h"
#include "test.h"

void render();

int main(int argc, char **argv) {
  test();
  //render();
  return 0;
}

void render() {
  Renderer renderer;
  renderer_initialize(&renderer);

  SDL_FillRect(renderer.surface, NULL, SDL_MapRGB(renderer.surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(renderer.window);
  SDL_Delay(2000);

  renderer_deinitialize(&renderer);
}
