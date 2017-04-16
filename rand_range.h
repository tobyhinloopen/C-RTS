#ifndef RAND_H
#define RAND_H

typedef unsigned int RandRangeSeed;

float rand_rangef(RandRangeSeed * seed, float min, float max);
int rand_rangei(RandRangeSeed * seed, int min, int max);
float rand_rangef_pow2(RandRangeSeed * seed, float min, float max);

#endif
