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
void setup_unit(Unit * unit);
float randf();
int event_is_window_resize(SDL_Event * event, SDL_Window * window);
int event_is_quit_request(SDL_Event * event);

int team_colors[] = { 0xFF0000, 0x00CC00, 0x4444FF, 0xCC8800 };
float team_spawns[][2] = { { -200.f, 200.f }, { 200.f, 200.f }, { -200.f, -200.f }, { 200.f, -200.f } };

int main(int argc, char **argv) {
  test();
  render();
  return 0;
}

void render() {
  Renderer renderer;
  renderer_initialize(&renderer);

  World world;
  world_initialize(&world);

  srand(time(NULL));

  for(int i=0; i<100; i++)
    setup_unit(&world_unit_allocate(&world)->unit);

  SDL_InitSubSystem(SDL_INIT_TIMER);
  unsigned int start_time = SDL_GetTicks();
  unsigned int last_time = start_time;

  int is_quit_requested = 0;
  while(!is_quit_requested) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event_is_quit_request(&event))
        is_quit_requested = 1;
      else if(event_is_window_resize(&event, renderer.window))
        renderer_notify_viewport_resized(&renderer);
    }

    unsigned int current_time = SDL_GetTicks();
    float delta = (current_time - last_time) / 1000.f;
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

void setup_unit(Unit * unit) {
  unit_initialize(unit);
  unit->angular_throttle = -1 + 2 * randf();
  unit->throttle = .5f + .5f * randf();
  unit->head_throttle = -1 + 2 * randf();
  unit->direction = PI2f * -.5f + randf() * PI2f;

  int team_offset = (int)(randf() * sizeof(team_colors) / sizeof(int));
  unit->team_id = team_colors[team_offset];
  unit->position.x = team_spawns[team_offset][0] + -80.f + randf() * 160.f;
  unit->position.y = team_spawns[team_offset][1] + -80.f + randf() * 160.f;
}

float randf() {
  return (float)((double)rand() / RAND_MAX);
}

int event_is_quit_request(SDL_Event * event) {
  return event->type == SDL_QUIT;
}

int event_is_window_resize(SDL_Event * event, SDL_Window * window) {
  return event->type == SDL_WINDOWEVENT
    && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED
    && event->window.windowID == SDL_GetWindowID(window);
}
