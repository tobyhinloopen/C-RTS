#include "mod_event.h"

#include "../vector3.h"
#include "../renderer.h"
#include <SDL2/SDL.h>

static void mod_event_initialize(Game * game) {
  game->is_quit_requested = 0;
}

static int event_is_window_resize(SDL_Event * event, SDL_Window * window) {
  return event->type == SDL_WINDOWEVENT
    && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED
    && event->window.windowID == SDL_GetWindowID(window);
}

static void handle_mouse_button_event(Game * game, SDL_MouseButtonEvent * event) {
  game->command_position_set = 1;
  Vector screen;
  screen.x = event->x;
  screen.y = event->y;
  game->command_position = renderer_screen_to_world(&game->renderer, screen);
}

static Vector3 camera_movement_from_keyboard_event(SDL_KeyboardEvent * event) {
  Vector3 movement = { 0.0f, 0.0f, 0.0f };

  if(!event->repeat) {
    switch(event->keysym.sym) {
      case SDLK_d:
      case SDLK_RIGHT:
      movement.x = 1.0f;
      break;

      case SDLK_a:
      case SDLK_LEFT:
      movement.x = -1.0f;
      break;

      case SDLK_w:
      case SDLK_UP:
      movement.y = 1.0f;
      break;

      case SDLK_s:
      case SDLK_DOWN:
      movement.y = -1.0f;
      break;

      case SDLK_q:
      movement.z = 1.0f;
      break;

      case SDLK_e:
      movement.z = -1.0f;
      break;
    }

    if(event->type == SDL_KEYUP)
      vector3_multiply_scalar(&movement, -1.0f);
  }

  return movement;
}

static void mod_event_update(Game * game, unsigned int delta) {
  game->command_position_set = 0;

  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT)
      game->is_quit_requested = 1;
    else if(event_is_window_resize(&event, game->renderer.window))
      game->is_window_resized = 1;
    else if(event.type == SDL_MOUSEBUTTONUP)
      handle_mouse_button_event(game, &event.button);
    else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
      vector3_add(&game->camera_movement, camera_movement_from_keyboard_event(&event.key));
  }
}

void mod_event(GameModule * mod) {
  mod->initialize = mod_event_initialize;
  mod->update = mod_event_update;
}
