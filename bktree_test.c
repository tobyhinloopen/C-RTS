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
#define BKTREE_CHECKED_FIND_COUNT 1
#define BKTREE_BENCHMARK_COUNT 1000
#define BKTREE_FIND_N 100
#define BKTREE_FIND_MAX_DISTANCE_SQ BKTREE_DISTANCE_MAX

// #define BKTREE_DEBUG_PRINT

static RandRangeSeed seed = 0;
static BKTree tree;
static BKNode nodes[BKTREE_NODE_COUNT];
static clock_t start;
static BKResult * find_closest_slowly_results;

#ifdef BKTREE_DEBUG_PRINT
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
#endif

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

#ifdef BKTREE_DEBUG_PRINT
static void report_time_spent(const char * desc) {
  clock_t duration = clock() - start;
  printf("%s took %luC\n", desc, duration);
}
#endif

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

static BKSize find_closest_slowly(BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance_sq) {
  for (int i = 0; i < BKTREE_NODE_COUNT; i++) {
    BKResult * current = find_closest_slowly_results + i;
    BKNode * node = nodes + i;
    current->value = node->value;
    current->distance_sq = distance_sq_node_to_xy(node, x, y);
  }

  qsort(find_closest_slowly_results, BKTREE_NODE_COUNT, sizeof(BKResult), compare_bkresult);

  BKSize result_count = MIN(n, BKTREE_NODE_COUNT);
  for (int i = 0; i < result_count; i++) {
    if (find_closest_slowly_results[i].distance_sq > max_distance_sq) {
      result_count = i;
      break;
    }
  }

  memcpy(results, find_closest_slowly_results, sizeof(BKResult) * result_count);
  return result_count;
}

#ifdef BKTREE_DEBUG_PRINT
static void print_result(BKResult result) {
  printf("  val:%6i - dis:%6i\n", result.value, result.distance_sq);
}
#endif

static void checked_find_multiple(BKScalar x, BKScalar y) {
  BKResult expected_results[BKTREE_FIND_N];
  memset(expected_results, 0, sizeof(expected_results));
  BKSize expected_size = find_closest_slowly(x, y, expected_results, BKTREE_FIND_N, BKTREE_FIND_MAX_DISTANCE_SQ);

#ifdef BKTREE_DEBUG_PRINT
  printf("EXPECTED %i RESULTS:\n", expected_size);
  for (int i = 0; i < expected_size; i++)
    print_result(expected_results[i]);
#endif

  BKResult actual_results[BKTREE_FIND_N];
  memset(actual_results, 0, sizeof(actual_results));
  BKSize actual_size = bktree_find(&tree, x, y, actual_results, BKTREE_FIND_N, BKTREE_FIND_MAX_DISTANCE_SQ);

#ifdef BKTREE_DEBUG_PRINT
  printf("ACTUALLY %i RESULTS:\n", actual_size);
  for (int i = 0; i < actual_size; i++)
    print_result(actual_results[i]);
#endif

  assert(actual_size == expected_size);
  for (int i = 0; i < actual_size; i++)
    assert(actual_results[i].distance_sq == expected_results[i].distance_sq);
}

void test_bktree() {
  find_closest_slowly_results = (BKResult *) malloc(sizeof(BKResult) * BKTREE_NODE_COUNT);
  assert(find_closest_slowly_results != NULL);

  populate_nodes();

  bktree_initialize(&tree);

  start = clock();
  bktree_build(&tree, nodes, BKTREE_NODE_COUNT);
#ifdef BKTREE_DEBUG_PRINT
  report_time_spent("bktree_build");
  bktree_print();
#endif

  for (int i = 0; i < BKTREE_CHECKED_FIND_COUNT; i++)
    checked_find_multiple(rand_bkscalar(), rand_bkscalar());

  bktree_deinitialize(&tree);
}
