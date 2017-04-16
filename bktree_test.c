#include "bktree.h"
#include "bktree_test.h"
#include <assert.h>
#include "rand_range.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#define BKTREE_NODE_COUNT 100000
#define BKTREE_CHECKED_FIND_COUNT 40
#define BKTREE_BENCHMARK_COUNT 1000
#define BKTREE_FIND_N 8
#define BKTREE_FIND_MAX_DISTANCE_SQ 2048

static RandRangeSeed seed = 0;
static BKTree tree;
static BKNode nodes[BKTREE_NODE_COUNT];
static clock_t start;
static BKResult * find_closest_slowly_results;

static void bktree_print_node(idx, depth) {
  assert(idx > 0);
  const BKNode * const node = tree.nodes + idx;
  printf("%*s(%5u,%5u) %5u\n", depth * 2, "", node->x, node->y, node->value);
  if (node->leaf)
    return;
  idx <<= 1;
  bktree_print_node(idx, depth + 1);
  bktree_print_node(idx + 1, depth + 1);
}

static void bktree_print() {
  printf("BKTREE DEBUG PRINT\ncapacity: %u\ncount: %u\n", tree.capacity, tree.count);
  bktree_print_node(1, 0);
}

static BKScalar rand_bkscalar() {
  return (BKScalar)rand_rangei(&seed, 0, BKTREE_SCALAR_MAX);
}

static void populate_nodes() {
  for (int i = 0; i < BKTREE_NODE_COUNT; i++) {
    BKNode * node = nodes + i;
    node->x = rand_bkscalar();
    node->y = rand_bkscalar();
    node->value = rand_rangei(&seed, 0, BKTREE_VALUE_MAX);
  }
}

static void report_time_spent(const char * desc) {
  clock_t duration = clock() - start;
  printf("%s took %luC\n", desc, duration);
}

static BKDistance sq(BKScalar a) {
  return a * a;
}

static BKScalar diff(BKScalar a, BKScalar b) {
  return a > b ? b - a : a - b;
}

static BKDistance distance_sq_node_to_xy(BKNode * node, BKScalar x, BKScalar y) {
  return sq(diff(x, node->x)) + sq(diff(y, node->y));
}

static int compare_bkresult(const void * a_ptr, const void * b_ptr) {
  BKDistance a = ((BKResult *)a_ptr)->distance_sq;
  BKDistance b = ((BKResult *)b_ptr)->distance_sq;
  return CMP(a, b);
}

static BKSize find_closest_slowly(BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance_sq) {;
  for (int i = 0; i < BKTREE_NODE_COUNT; i++) {
    BKResult * current = find_closest_slowly_results + i;
    BKNode * node = nodes + i;
    current->value = node->value;
    current->distance_sq = distance_sq_node_to_xy(node, x, y);
  }

  qsort(find_closest_slowly_results, BKTREE_NODE_COUNT, sizeof(BKResult), compare_bkresult);

  int count_within_distance_sq = 0;
  for (int i = 0; i < BKTREE_NODE_COUNT; i++) {
    if (find_closest_slowly_results[i].distance_sq > max_distance_sq) {
      count_within_distance_sq = i;
      break;
    }
  }

  BKSize result_count = MIN(count_within_distance_sq, MIN(n, BKTREE_NODE_COUNT));
  memcpy(results, find_closest_slowly_results, sizeof(BKResult) * result_count);
  return result_count;
}

static void checked_find_multiple(BKScalar x, BKScalar y) {
  BKResult expected_results[BKTREE_FIND_N];
  BKSize expected_size = find_closest_slowly(x, y, expected_results, BKTREE_FIND_N, BKTREE_FIND_MAX_DISTANCE_SQ);

  BKResult actual_results[BKTREE_FIND_N];
  BKSize actual_size = bktree_find(&tree, x, y, actual_results, BKTREE_FIND_N, BKTREE_FIND_MAX_DISTANCE_SQ);

  assert(actual_size == expected_size);
  assert(strncmp((const char *)actual_results, (const char *)expected_results, sizeof(BKResult) * actual_size) == 0);
}

void test_bktree() {
  find_closest_slowly_results = (BKResult*)malloc(sizeof(BKResult) * BKTREE_NODE_COUNT);
  assert(find_closest_slowly_results != NULL);

  populate_nodes();

  bktree_initialize(&tree);

  start = clock();
  bktree_build(&tree, nodes, BKTREE_NODE_COUNT);
  report_time_spent("bktree_build");
  // bktree_print();

  for (int i = 0; i < BKTREE_CHECKED_FIND_COUNT; i++)
    checked_find_multiple(rand_bkscalar(), rand_bkscalar());

  // BKSize bktree_find(BKTree * tree, BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance);
  // BKResult bktree_first(BKTree * tree, BKScalar x, BKScalar y);

  bktree_deinitialize(&tree);
}
