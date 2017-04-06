#include "rand_range.h"

#include <math.h>

#define RAND_MAX 32767

static int rand(rand_range_seed_t * seed) {
  (*seed) = (*seed) * 1103515245 + 12345;
  return (unsigned int)((*seed)/65536) % 32768;
}

float rand_rangef(rand_range_seed_t * seed, float min, float max) {
  return min + ((double)rand(seed) / RAND_MAX) * (max - min);
}

int rand_rangei(rand_range_seed_t * seed, int min, int max) {
  return rand_rangef(seed, min, max);
}

float rand_rangef_pow2(rand_range_seed_t * seed, float min, float max) {
  const float magnitude = (max - min)/2;
  const float magnitude_sq = magnitude * magnitude;
  const float result = rand_rangef(seed, -magnitude_sq, magnitude_sq);
  return sqrtf(result < 0.0f ? -result : result) * (result < 0.0f ? -1.0f : 1.0f);
}
