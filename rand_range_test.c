#include "rand_range_test.h"
#include "rand_range.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int errors_count = 0;

static void assert_determenistic_random(int expected_result, int actual_result) {
  if (actual_result != expected_result) {
    printf("Expected %i to be %i\n", actual_result, expected_result);
    errors_count++;
  }
}

void test_rand_range() {
  RandRangeSeed seed = 0;
  assert_determenistic_random( 17274, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(  3586, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-60254, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-60722, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-56322, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random( 19146, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random( -3014, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  assert_determenistic_random(-13510, rand_rangei(&seed, -0xFFFF, 0xFFFF));
  if (errors_count)
    assert(0);
}
