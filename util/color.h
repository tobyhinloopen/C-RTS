#ifndef VIEW_COLOR_H
#define VIEW_COLOR_H

#include "stdint.h"

typedef union {
  uint32_t value;
  struct {
    uint8_t r, g, b, a;
  };
} Color;

#endif
