#include "projectile.h"
#include <math.h>

const float PROJECTILE_PIXELS_PER_SECOND = 600.0f;
const float PROJECTILE_RANGE = 1000.0f;

void projectile_initialize(Projectile * projectile, Vector position, float direction, int team_id) {
  projectile->position = position;
  projectile->direction = direction;
  projectile->team_id = team_id;
  projectile->distance_remaining = PROJECTILE_RANGE;
}

void projectile_update(Projectile * projectile, float delta) {
  float distance = PROJECTILE_PIXELS_PER_SECOND * delta;
  if(projectile->distance_remaining <= distance)
    distance = projectile->distance_remaining;
  projectile->distance_remaining -= PROJECTILE_PIXELS_PER_SECOND * delta;
  if(distance > 0)
    vector_add(&projectile->position,
      (Vector){ distance * cosf(projectile->direction), distance * sinf(projectile->direction) });
}
