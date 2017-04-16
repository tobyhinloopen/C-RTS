#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)
#define CMP(a, b) ((a) < (b) ? -1 : ((a) > (b) ? 1 : 0))

#define SWAP(T, a, b) do { T tmp = b; b = a; a = tmp; } while (0)

#define PARTITION(T, F, ptr, _l, _r, idx_pivot) do { \
  T * ptr_l = &ptr[_l]; \
  T * ptr_r = &ptr[_r]; \
  T * ptr_pivot = &ptr[idx_pivot]; \
  do { \
    if (ptr_pivot->F < ptr_l->F) \
      SWAP(T, *ptr_pivot, *ptr_l); \
    if (ptr_r->F < ptr_pivot->F) { \
      SWAP(T, *ptr_pivot, *ptr_r); \
      if (ptr_pivot->F < ptr_l->F) \
        SWAP(T, *ptr_pivot, *ptr_l); \
    } \
    ptr_l++; \
    ptr_r--; \
    SWAP(T, *ptr_pivot, *ptr_r); \
    T * ptr_store = ptr_l; \
    for (T * ptr_i = ptr_l; ptr_i < ptr_r; ptr_i++) { \
      if (ptr_i->F < ptr_pivot->F) { \
        SWAP(T, *ptr_store, *ptr_i); \
        ptr_store++; \
      } \
    } \
    SWAP(T, *ptr_r, *ptr_store); \
    if (ptr_store > ptr_pivot) \
      ptr_r = ptr_store - 1; \
    else if (ptr_store < ptr_pivot) \
      ptr_l = ptr_store + 1; \
    else \
      break; \
  } while (1); \
} while (0)

unsigned int log2i_ceil(unsigned int);

#endif
