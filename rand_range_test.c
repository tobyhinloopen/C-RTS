#include "rand_range_test.h"
#include "rand_range.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void assert_determenistic_random(int expected_result, int actual_result) {
  if (actual_result != expected_result) {
    printf("Expected %i to be %i\n", actual_result, expected_result);
  }
}

void test_rand_range() {
  rand_range_seed_t seed = 0;
  assert_determenistic_random(  1818, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-42502, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-25082, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(  4526, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random( 58670, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-43026, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random( 26506, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-35858, rand_rangei(&seed, -0xFFFF, 0xFFFF));
}
