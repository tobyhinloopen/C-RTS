#include "rand_range.h"

#include <math.h>
#include <stdlib.h>

float rand_rangef(float min, float max) {
  return min + ((double)rand() / RAND_MAX) * (max - min);
}

int rand_rangei(int min, int max) {
  return rand_rangef(min, max);
}

float rand_rangef_pow2(float min, float max) {
  const float magnitude = (max - min)/2;
  const float magnitude_sq = magnitude * magnitude;
  const float result = rand_rangef(-magnitude_sq, magnitude_sq);
  return sqrtf(result < 0.0f ? -result : result) * (result < 0.0f ? -1.0f : 1.0f);
}
