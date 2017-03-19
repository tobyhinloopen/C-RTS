#include "camera.h"

const float CAMERA_SPEED = 512.0f;

void camera_update(Vector3 * camera, Vector3 camera_movement, float delta) {
  const float camera_delta = delta * CAMERA_SPEED;
  vector3_multiply(&camera_movement, (Vector3) { camera_delta, camera_delta, delta });
  vector3_add(camera, camera_movement);
}
