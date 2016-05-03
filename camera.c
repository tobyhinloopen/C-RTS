#include "camera.h"

const float CAMERA_SPEED = 512.0f;

Vector3 camera_movement_from_keyboard_event(SDL_KeyboardEvent * event) {
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

void camera_update(Vector3 * camera, Vector3 camera_movement, float delta) {
  const float camera_delta = delta * CAMERA_SPEED;
  vector3_multiply(&camera_movement, (Vector3) { camera_delta, camera_delta, delta });
  vector3_add(camera, camera_movement);
}
