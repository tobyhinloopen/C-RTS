#ifndef UNIT_BEHAVIOR_H
#define UNIT_BEHAVIOR_H

#include "../vector.h"
#include "../unit.h"
#include "../world.h"

Unit * unit_behavior_find_closest_enemy_unit(Unit *, World *);
void unit_behavior_stop(Unit *);
void unit_behavior_look_at(Unit *, Vector target_position);
void unit_behavior_look_forward(Unit *);
void unit_behavior_set_target_position(Unit *, Vector target_position, float min_distance);
void unit_behavior_open_fire(Unit *);
void unit_behavior_hold_fire(Unit *);

#endif
