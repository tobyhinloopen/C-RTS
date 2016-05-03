#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include <SDL2/SDL.h>

Vector3 camera_movement_from_keyboard_event(SDL_KeyboardEvent *);
void camera_update(Vector3 * camera, Vector3 camera_movement, float delta);

#endif
