#ifndef UNIT_BEHAVIOR_H
#define UNIT_BEHAVIOR_H

#include "../vector.h"
#include "../unit.h"
#include "../world.h"

void unit_behavior_movement_stop(Unit * unit);
void unit_behavior_head_stop(Unit *);
void unit_behavior_look_at(Unit *, Vector target_position);
void unit_behavior_look_forward(Unit *);
void unit_behavior_move_away_from(Unit *, Vector position);
void unit_behavior_evasive_flee_from(Unit *, Vector position);
void unit_behavior_overdrive(Unit *);
void unit_behavior_head_engage_position(Unit *, Vector target_position);
void unit_behavior_set_target_position(Unit *, Vector target_position, float min_distance);
void unit_behavior_open_fire(Unit *);
void unit_behavior_hold_fire(Unit *);

#endif
