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

const int TEAM_COUNT = 4;
const int TEAM_COLOR[TEAM_COUNT] = { 0xFF0000, 0x00CC00, 0x4444FF, 0xCC8800 };
const float TEAM_SPAWN[TEAM_COUNT][2] = { { -320, 240 }, { 320, 240 }, { -320, -240 }, { 320, -240 } };
const int UNIT_SPAWN_INTERVAL = 100;

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

  for(int i=0; i<4; i++)
    setup_unit(&world_unit_allocate(&world)->unit);

  SDL_InitSubSystem(SDL_INIT_TIMER);
  unsigned int start_time = SDL_GetTicks();
  unsigned int last_time = start_time;
  unsigned int last_spawn_time = last_time;

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

    while(last_spawn_time + UNIT_SPAWN_INTERVAL <= current_time) {
      last_spawn_time += UNIT_SPAWN_INTERVAL;
      setup_unit(&world_unit_allocate(&world)->unit);
    }

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

  int team_offset = randf() * TEAM_COUNT;
  unit->team_id = TEAM_COLOR[team_offset];
  unit->position.x = TEAM_SPAWN[team_offset][0] + -80.f + randf() * 160.f;
  unit->position.y = TEAM_SPAWN[team_offset][1] + -80.f + randf() * 160.f;
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
