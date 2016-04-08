#ifndef UNIT_MOVEMENT_H
#define UNIT_MOVEMENT_H

#include "../vector.h"
#include "../unit.h"

void unit_movement_set_target_position(Unit *, Vector target_position, float min_distance);

#endif
