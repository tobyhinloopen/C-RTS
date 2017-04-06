#include "rand_range_test.h"
#include "rand_range.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void assert_determenistic_random(int actual_result, int expected_result) {
  if (actual_result != expected_result) {
    printf("Expected %i to be %i\n", actual_result, expected_result);
    assert(0);
  }
}

void test_rand_range() {
  srand(0);
  assert_determenistic_random(-33740, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random(-63769, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random(-15316, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random(-11186, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random(-56652, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random( 64634, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random(- 2056, rand_rangei(-0xFFFF, 0xFFFF));
  assert_determenistic_random( 34777, rand_rangei(-0xFFFF, 0xFFFF));
}
