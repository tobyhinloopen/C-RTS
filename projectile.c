#include "projectile.h"
#include <math.h>

const float PROJECTILE_PIXELS_PER_SECOND = 600.0f;
const float PROJECTILE_RANGE = 1000.0f;
const float PROJECTILE_DECAY = 1.0f;

void projectile_initialize(Projectile * projectile, Vector position, float direction, int team_id) {
  projectile->position = position;
  projectile->hit_count = 0;
  projectile->direction = direction;
  projectile->team_id = team_id;
  projectile->distance_remaining = PROJECTILE_RANGE;
  projectile->decay_remaining = PROJECTILE_DECAY;
}

static float projectile_update_movement(Projectile * projectile, float delta) {
  float distance = PROJECTILE_PIXELS_PER_SECOND * delta;
  if(projectile->distance_remaining < distance) {
    distance = projectile->distance_remaining;
    projectile->distance_remaining = 0;
  } else
    projectile->distance_remaining -= distance;
  vector_add(&projectile->position,
    (Vector){ distance * cosf(projectile->direction), distance * sinf(projectile->direction) });
  return distance / PROJECTILE_PIXELS_PER_SECOND;
}

void projectile_update(Projectile * projectile, float delta) {
  if(projectile->distance_remaining > 0)
    delta -= projectile_update_movement(projectile, delta);
  if(delta > 0)
    projectile->decay_remaining -= delta;
}

float projectile_damage(Projectile * projectile) {
  return 100.0f;
}

int projectile_is_dead(Projectile * projectile) {
  return projectile->decay_remaining <= 0.0f;
}
