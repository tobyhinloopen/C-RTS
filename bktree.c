#include "bktree.h"
#include <assert.h>
#include <stdlib.h>
#include "util.h"

// #define BKTREE_PARTITIONER_QSORT
#define BKTREE_PARTITIONER_MACRO

void bktree_initialize(BKTree * tree) {
  tree->nodes = NULL;
  tree->depth = 0;
  tree->count = 0;
  tree->capacity = 0;
}

static void bkdtree_realloc(BKTree * tree, BKSize n) {
  tree->depth = log2i_ceil(n);
  tree->capacity = 1 << (tree->depth + 1);
  tree->nodes = realloc(tree->nodes, sizeof(BKNode) * tree->capacity);
  assert(tree->nodes != NULL);
}

static int compare_node_x(const void * a_ptr, const void * b_ptr) {
  const BKScalar a = ((const BKNode *)a_ptr)->x;
  const BKScalar b = ((const BKNode *)b_ptr)->x;
  return CMP(a, b);
}

static int compare_node_y(const void * a_ptr, const void * b_ptr) {
  const BKScalar a = ((const BKNode *)a_ptr)->y;
  const BKScalar b = ((const BKNode *)b_ptr)->y;
  return CMP(a, b);
}

static void build_resursive(BKNode * target_nodes, BKSize idx, BKNode * input_nodes, BKSize left, BKSize right, BKBool odd) {
  const BKSize m = (left + right + 1) >> 1;
  const BKSize count = right - left + 1;
  BKNode * const target_node = target_nodes + idx;
  (*target_node) = input_nodes[m];
  target_node->leaf = count >= 2 ? 0 : 1;
  if (target_node->leaf)
    return;

#ifdef BKTREE_PARTITIONER_QSORT
  qsort(input_nodes + left, count, sizeof(BKNode), odd ? compare_node_y : compare_node_x);
#endif
#ifdef BKTREE_PARTITIONER_MACRO
  if (odd)
    PARTITION(BKNode, y, input_nodes, left, right, m);
  else
    PARTITION(BKNode, x, input_nodes, left, right, m);
#endif

  idx <<= 1;
  build_resursive(target_nodes, idx, input_nodes, left, m - 1, !odd);
  build_resursive(target_nodes, idx + 1, input_nodes, m, right, !odd);
}

void bktree_build(BKTree * tree, BKNode * input_nodes, BKSize n) {
  bkdtree_realloc(tree, n);
  tree->count = n;
  build_resursive(tree->nodes, 1, input_nodes, 0, n - 1, 0);
}

BKSize bktree_find(BKTree * tree, BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance_sq) {
  return 0;
}

BKResult bktree_first(BKTree * tree, BKScalar x, BKScalar y) {
  return (BKResult){};
}

void bktree_deinitialize(BKTree * tree) {

}
