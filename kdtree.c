#include "kdtree.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

void kdtree_initialize(KDTree * kdtree) {
  kdtree->capacity = 0;
  kdtree->count = 0;
  kdtree->items = NULL;
  kdtree->nodes = NULL;
}

void kdtree_set_capacity(KDTree * kdtree, size_t capacity) {
  kdtree->nodes = realloc(kdtree->nodes, sizeof(KDTreeNode) * capacity);
  assert(kdtree->nodes != NULL);
  kdtree->items = realloc(kdtree->items, sizeof(KDTreeItem) * capacity);
  assert(kdtree->items != NULL);
  kdtree->capacity = capacity;
}

void kdtree_clear(KDTree * kdtree) {
  kdtree->count = 0;
}

void kdtree_add(KDTree * kdtree, Vector position, void * ref) {
  assert(kdtree->count < kdtree->capacity);
  KDTreeItem * item = &kdtree->items[kdtree->count++];
  item->position = position;
  item->ref = ref;
}

static Vector load_item_position(const void * item_ptr) {
  return ((const KDTreeItem *)item_ptr)->position;
}

static int compare_float(float a, float b) {
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

static int compare_item_x(const void * a, const void * b) {
  return compare_float(load_item_position(a).x, load_item_position(b).x);
}

static int compare_item_y(const void * a, const void * b) {
  return compare_float(load_item_position(a).y, load_item_position(b).y);
}

static KDTreeNode * get_next_node(KDTree * kdtree, int * count) {
  assert(*count < kdtree->count);
  return &kdtree->nodes[(*count)++];
}

static KDTreeNode * build_recursive_node(KDTree * kdtree, KDTreeItem * items, size_t items_length, int depth, int * count) {
  if (items_length == 0)
    return NULL;

  int (*compare_fn)(const void *, const void *) = depth%2 == 0 ? compare_item_x : compare_item_y;
  qsort(items, items_length, sizeof(KDTreeItem), compare_fn);

  KDTreeNode * node = get_next_node(kdtree, count);
  size_t median_item_index = items_length / 2;

  while (median_item_index > 0 && compare_fn(&items[median_item_index], &items[median_item_index-1]) == 0) {
    median_item_index--;
  }

  size_t right_item_index = median_item_index + 1;

  node->item = items[median_item_index];
  node->left = build_recursive_node(kdtree, &items[0], median_item_index, depth+1, count);
  node->right = build_recursive_node(kdtree, &items[right_item_index], items_length - right_item_index, depth+1, count);

  return node;
}

void kdtree_build(KDTree * kdtree) {
  if (kdtree->count == 0)
    return;

  int count = 0;
  build_recursive_node(kdtree, kdtree->items, kdtree->count, 0, &count);
  assert(count == kdtree->count);
}

typedef struct {
  float distance;
  KDTreeNode * node;
} KDTreeNodeDistance;

static KDTreeNodeDistance get_node_distance(KDTreeNode * node, Vector position) {
  assert(node != NULL);
  return (KDTreeNodeDistance){ vector_sq_distance(node->item.position, position), node };
}

static float get_position_on_axis(Vector vector, int depth) {
  return depth%2 == 0 ? vector.x : vector.y;
}

static KDTreeNodeDistance get_closer_node_distance(KDTreeNodeDistance current_nd, Vector position, int depth) {
  KDTreeNode * current_node = current_nd.node;
  float current_position = get_position_on_axis(current_node->item.position, depth);
  float target_position = get_position_on_axis(position, depth);
  int position_comparison = target_position >= current_position;

  KDTreeNodeDistance current_best_nd;
  KDTreeNode * next_node = position_comparison ? current_node->right : current_node->left;
  if (next_node == NULL)
    current_best_nd = current_nd;
  else {
    KDTreeNodeDistance next_nd = get_node_distance(next_node, position);
    KDTreeNodeDistance closest_nd = get_closer_node_distance(next_nd, position, depth+1);
    current_best_nd = closest_nd.distance < current_nd.distance ? closest_nd : current_nd;
  }

  KDTreeNode * other_node = position_comparison ? current_node->left : current_node->right;
  if (other_node != NULL) {
    float splitting_coord_diff = current_position - target_position;
    if (splitting_coord_diff * splitting_coord_diff < current_best_nd.distance) {
      KDTreeNodeDistance other_nd = get_node_distance(other_node, position);
      KDTreeNodeDistance other_best_nd = get_closer_node_distance(other_nd, position, depth+1);
      current_best_nd = other_best_nd.distance < current_best_nd.distance ? other_best_nd : current_best_nd;
    }
  }

  return current_best_nd;
}

KDTreeFindResult kdtree_find_distance(KDTree * kdtree, Vector position) {
  if (!kdtree->count)
    return (KDTreeFindResult){ NULL, FP_INFINITE };
  KDTreeNode * current_node = &kdtree->nodes[0];
  KDTreeNodeDistance nd = get_node_distance(current_node, position);
  KDTreeNodeDistance result = get_closer_node_distance(nd, position, 0);
  return (KDTreeFindResult){ result.node->item.ref, result.distance };
}

void * kdtree_find(KDTree * kdtree, Vector position) {
  return kdtree_find_distance(kdtree, position).ref;
}

static void kdtree_debug_print_node(int depth, KDTreeNode * node, void * param, void (* print_fn)(void * ref, void * param)) {
  if (node == NULL) {
    return;
  }
  printf("%*s(%4.1f,%4.1f) ", depth * 2, "", node->item.position.x, node->item.position.y);
  print_fn(node->item.ref, param);
  printf("\n");
  kdtree_debug_print_node(depth+1, node->left, param, print_fn);
  kdtree_debug_print_node(depth+1, node->right, param, print_fn);
}

void kdtree_debug_print(KDTree * kdtree, void * param, void (* print_fn)(void * ref, void * param)) {
  printf("KDTREE DEBUG PRINT\ncapacity: %zu\ncount: %zu\n", kdtree->capacity, kdtree->count);
  kdtree_debug_print_node(0, &kdtree->nodes[0], param, print_fn);
}

void kdtree_deinitialize(KDTree * kdtree) {
  free(kdtree->nodes);
  kdtree->nodes = NULL;
  free(kdtree->items);
  kdtree->items = NULL;
  kdtree->capacity = 0;
  kdtree->count = 0;
}
