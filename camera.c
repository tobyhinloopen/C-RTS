#include "camera.h"

const float CAMERA_SPEED = 512.0f;

void camera_update(Vector3 * camera, Vector3 camera_movement, float delta) {
  const float camera_delta = delta * CAMERA_SPEED * (1 + camera->z);
  vector3_multiply(&camera_movement, (Vector3) { camera_delta, camera_delta, delta * (1 + camera->z) });
  vector3_add(camera, camera_movement);
  if (camera->z < 0)
    camera->z = 0;
  if (camera->z > 4)
    camera->z = 4;
}
