#include "bktree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void bktree_initialize(BKTree * tree) {
  tree->nodes = NULL;
  tree->depth = 0;
  tree->count = 0;
  tree->capacity = 0;
}

static void bkdtree_realloc(BKTree * tree, BKSize n) {
  tree->depth = n == 0 ? 0 : log2i_ceil(n);
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

  qsort(input_nodes + left, count, sizeof(BKNode), odd ? compare_node_y : compare_node_x);

  idx <<= 1;
  build_resursive(target_nodes, idx, input_nodes, left, m - 1, !odd);
  build_resursive(target_nodes, idx + 1, input_nodes, m, right, !odd);
}

void bktree_build(BKTree * tree, BKNode * input_nodes, BKSize n) {
  bkdtree_realloc(tree, n);
  tree->count = n;
  build_resursive(tree->nodes, 1, input_nodes, 0, n - 1, 0);
}

static void maybe_insert_result_sorted(BKResult * results, BKSize * result_count_ptr, BKSize n, BKDistance distance_sq, BKValue value) {
  assert(n > 0);
  const BKSize result_count = *result_count_ptr;

  // There are no results yet, just insert it
  if (result_count == 0) {
    results->value = value;
    results->distance_sq = distance_sq;
    (*result_count_ptr) = 1;
    return;
  }

  // There is one result, and only rooom for one result. Insert it.
  if (result_count == 1 && n == 1) {
    if (results->distance_sq > distance_sq) {
      results->value = value;
      results->distance_sq = distance_sq;
    }
    return;
  }

  // There is at least 1 result. Insert sorted, smallest distance first.
  // Find the first record that has a smaller distance than the value to insert.
  BKSize insert_idx = 0;
  while (results[insert_idx].distance_sq < distance_sq && insert_idx < result_count)
    insert_idx++;

  // If the index equals to the count, it means the new record has the greatest distance. We insert
  // the record at the end of the list if there is room for it.
  if (insert_idx == result_count) {
    if (result_count < n) {
      results[insert_idx].value = value;
      results[insert_idx].distance_sq = distance_sq;
      (*result_count_ptr)++;
    }
    return;
  }

  // All passed records have smaller distance and will remain in the set. The remaining records (if
  // any) will be moved to the right, optionally removing the last.
  BKSize records_to_move = MIN(result_count - insert_idx, n - insert_idx - 1);
  memmove(results + insert_idx + 1, results + insert_idx, sizeof(BKResult) * records_to_move);
  results[insert_idx].value = value;
  results[insert_idx].distance_sq = distance_sq;
  if (result_count < n)
    (*result_count_ptr)++;
}

static BKDistance node_distance_sq(BKNode node, BKScalar x, BKScalar y) {
  int diff_x = (int)node.x - x;
  int diff_y = (int)node.y - y;
  return diff_x * diff_x + diff_y * diff_y;
}

BKSize bktree_find(BKTree * tree, BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance_sq) {
  if (n == 0) {
    return 0;
  }
  BKNode node;
  BKSize n_idx = 1;
  int down = 1;
  BKSize depth = 1;
  BKSize dcode = 0;
  BKSize result_count = 0;

  while (depth > 0) {
    node = tree->nodes[n_idx];
    int pd = (depth % 2) ? x - node.x : y - node.y;
    if (down) {
      if (!node.leaf) {
        depth <<= 1;
        n_idx <<= 1;
        if (pd >= 0) {
          n_idx++;
        }
      } else {
        down = 0;
        depth >>= 1;
        n_idx >>= 1;
        BKDistance distance_sq = node_distance_sq(node, x, y);
        if (distance_sq <= max_distance_sq)
          maybe_insert_result_sorted(results, &result_count, n, distance_sq, node.value);
      }
    } else {
      int pd_sq = pd * pd;
      if (dcode < depth && pd_sq < max_distance_sq /*&& (result_count == 0 || result_count < n || pd_sq < results[result_count-1].distance_sq)*/) {
        down = 1;
        dcode += depth;
        depth <<= 1;
        n_idx <<= 1;
        if (pd < 0) {
          n_idx++;
        }
      } else {
        dcode -= (dcode < depth) ? 0 : depth;
        depth >>= 1;
        n_idx >>= 1;
      }
    }
  }

  return result_count;
}

BKResult bktree_first(BKTree * tree, BKScalar x, BKScalar y) {
  BKResult result = {0, BKTREE_DISTANCE_MAX};
  bktree_find(tree, x, y, &result, 1, BKTREE_SIZE_MAX);
  return result;
}

void bktree_deinitialize(BKTree * tree) {
  free(tree->nodes);
  tree->nodes = NULL;
}
