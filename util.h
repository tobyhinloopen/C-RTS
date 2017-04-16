#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)
#define CMP(a, b) ((a) < (b) ? -1 : ((a) > (b) ? 1 : 0))

#define SWAP(T, a, b) do { T tmp = b; b = a; a = tmp; } while (0)

unsigned int log2i_ceil(unsigned int);

#endif
