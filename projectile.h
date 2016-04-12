#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vector.h"

extern const float PROJECTILE_PIXELS_PER_SECOND;

typedef struct {
  Vector position;
  float direction;
  int team_id;
  float distance_remaining;
} Projectile;

void projectile_initialize(Projectile *, Vector position, float direction, int team_id);
void projectile_update(Projectile *, float delta);

#endif
