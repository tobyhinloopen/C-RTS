#include "util_test.h"
#include "util.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static void test_log2i_ceil() {
  assert(log2i_ceil(255) == 8);
  assert(log2i_ceil(900) == 10);
}

static void test_swap() {
  int x = 4;
  int y = 3;
  SWAP(int, x, y);
  assert(y == 4);
  assert(x == 3);
}

void test_util() {
  test_log2i_ceil();
  test_swap();
}
