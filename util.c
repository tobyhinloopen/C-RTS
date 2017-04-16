#include "util.h"
#include <assert.h>
#include <string.h>

unsigned int log2i_ceil(unsigned int x) {
  assert(x > 0);
  return sizeof(int) * 8 - __builtin_clz(x);
}
