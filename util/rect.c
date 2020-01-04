#include "./rect.h"

void rect_resize_center(Rect * rect, Vector size) {
  rect->size = size;
  Vector half_size = size;
  vector_multiply_scalar(&half_size, 0.5);
  rect->top_left = rect->center;
  vector_add(&rect->top_left, half_size);
  rect->bottom_right = rect->center;
  vector_add(&rect->bottom_right, half_size);
}

void rect_resize_top_left(Rect * rect, Vector size) {
  rect->size = size;
  Vector half_size = size;
  vector_multiply_scalar(&half_size, 0.5);
  rect->bottom_right = rect->top_left;
  vector_add(&rect->bottom_right, size);
  vector_add(&rect->center, half_size);
}

void rect_move_top_left(Rect * rect, Vector top_left) {
  Vector distance = top_left;
  vector_subtract(&distance, rect->top_left);
  rect_move_by(rect, distance);
}

void rect_move_center(Rect * rect, Vector center) {
  Vector distance = center;
  vector_subtract(&distance, rect->center);
  rect_move_by(rect, distance);
}

void rect_move_by(Rect * rect, Vector distance) {
  vector_add(&rect->top_left, distance);
  vector_add(&rect->bottom_right, distance);
  vector_add(&rect->center, distance);
}

int rect_contains(Rect * const rect, Vector point) {
  return rect->top_left.x <= point.x
    && rect->top_left.y <= point.y
    && rect->bottom_right.x >= point.x
    && rect->bottom_right.y >= point.y;
}
