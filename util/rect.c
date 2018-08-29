#include "./rect.h"

void recti_set(Recti * rect, int x, int y, int w, int h) {
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
}
