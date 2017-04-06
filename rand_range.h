#ifndef RAND_H
#define RAND_H

typedef unsigned long int rand_range_seed_t;

float rand_rangef(rand_range_seed_t * seed, float min, float max);
int rand_rangei(rand_range_seed_t * seed, int min, int max);
float rand_rangef_pow2(rand_range_seed_t * seed, float min, float max);

#endif
