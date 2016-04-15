#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vector.h"

extern const float PROJECTILE_PIXELS_PER_SECOND;
extern const float PROJECTILE_RANGE;
extern const float PROJECTILE_DECAY;

typedef struct {
  Vector position;
  float direction;
  int team_id;
  float distance_remaining;
  float decay_remaining;
} Projectile;

void projectile_initialize(Projectile *, Vector position, float direction, int team_id);
void projectile_update(Projectile *, float delta);
float projectile_damage(Projectile *);
int projectile_is_dead(Projectile *);

#endif
