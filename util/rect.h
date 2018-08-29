#ifndef UTIL_RECT_H
#define UTIL_RECT_H

typedef struct {
  int x, y, w, h;
} Recti;

typedef struct {
  float x, y, w, h;
} Rectf;

void recti_set(Recti *, int, int, int, int);

#endif
