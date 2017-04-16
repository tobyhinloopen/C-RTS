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

typedef struct {
  int x;
} PartitionData;

#define PARTITION_K 10

static void test_partition() {
  PartitionData data[20] = { {9}, {6}, {7}, {0}, {2}, {8}, {1}, {5}, {3}, {4}, {9}, {6}, {7}, {0}, {2}, {8}, {1}, {5}, {3}, {4} };
  for (int i = 0; i < 20; i++) {
    if (i == PARTITION_K)
      printf("  ");
    printf("%i ", data[i].x);
  }
  printf("\n");
  PARTITION(PartitionData, x, data, 0, 19, PARTITION_K);
  int lmax = -1;
  int rmin = 10;
  for (int i = 0; i < 20; i++) {
    if (i < PARTITION_K)
      lmax = MAX(lmax, data[i].x);
    else if (i >= PARTITION_K)
      rmin = MIN(rmin, data[i].x);
    if (i == PARTITION_K)
      printf("  ");
    printf("%i ", data[i].x);
  }
  printf("\nlmax %i                rmin %i\n", lmax, rmin);
  assert(lmax < rmin);
}

void test_util() {
  test_log2i_ceil();
  test_swap();
  test_partition();
}
