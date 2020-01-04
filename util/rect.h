#pragma once

#include "../vector.h"

/**
 * A struct containing
 */
typedef struct {
  Vector top_left;
  Vector bottom_right;
  Vector size;
  Vector center;
} Rect;

void rect_resize_center(Rect * rect, Vector size);
void rect_resize_top_left(Rect * rect, Vector size);
void rect_move_top_left(Rect * rect, Vector top_left);
void rect_move_center(Rect * rect, Vector center);
void rect_move_by(Rect * rect, Vector distance);
int rect_contains(Rect * const rect, Vector point);
