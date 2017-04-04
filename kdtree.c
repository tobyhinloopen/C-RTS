#include "kdtree.h"
#include <stdlib.h>
#include <assert.h>

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

  qsort(items, items_length, sizeof(KDTreeItem), depth%2 == 0 ? compare_item_x : compare_item_y);

  KDTreeNode * node = get_next_node(kdtree, count);
  size_t median_item_index = items_length / 2;
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
  return (KDTreeNodeDistance){ vector_distance(node->item.position, position), node };
}

static KDTreeNodeDistance get_closer_node_distance(KDTreeNodeDistance current_nd, Vector position, int depth) {
  KDTreeNode * current_node = current_nd.node;
  float current_position;
  float target_position;
  if (depth%2 == 0) {
    current_position = current_node->item.position.x;
    target_position = position.x;
  } else {
    current_position = current_node->item.position.y;
    target_position = position.y;
  }
  KDTreeNode ** ref_next = target_position > current_position ? &current_node->right : &current_node->left;
  if (*ref_next == NULL) {
    return current_nd;
  } else {
    KDTreeNodeDistance next_nd = get_node_distance(*ref_next, position);
    KDTreeNodeDistance closest_nd = get_closer_node_distance(next_nd, position, depth+1);
    return closest_nd.distance < current_nd.distance ? closest_nd : current_nd;
  }
}

void * kdtree_find(KDTree * kdtree, Vector position) {
  if (!kdtree->count)
    return NULL;
  KDTreeNode * current_node = &kdtree->nodes[0];
  KDTreeNodeDistance nd = get_node_distance(current_node, position);
  return get_closer_node_distance(nd, position, 0).node->item.ref;
}

void kdtree_deinitialize(KDTree * kdtree) {
  free(kdtree->nodes);
  kdtree->nodes = NULL;
  free(kdtree->items);
  kdtree->items = NULL;
  kdtree->capacity = 0;
  kdtree->count = 0;
}
