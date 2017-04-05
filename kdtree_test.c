#include "kdtree_test.h"
#include "kdtree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int id;
  Vector position;
} KDTreeTestPoint;

#define KDTREE_TEST_POINTS_COUNT 8

KDTreeTestPoint test_points[KDTREE_TEST_POINTS_COUNT] = {
  {1,{7,2}}, {2,{5,4}}, {3,{9,6}}, {4,{2,3}}, {5,{4,7}}, {6,{8,1}}, {7,{7,3}}, {8,{6.9,3}}
};

void test_kdtree() {
  KDTree kdtree;

  kdtree_initialize(&kdtree);
  assert(kdtree.nodes == NULL);
  assert(kdtree.capacity == 0);
  assert(kdtree.count == 0);

  kdtree_set_capacity(&kdtree, KDTREE_TEST_POINTS_COUNT);
  assert(kdtree.capacity >= KDTREE_TEST_POINTS_COUNT);
  assert(kdtree.count == 0);
  assert(kdtree.nodes != NULL);

  for (int i = 0; i < KDTREE_TEST_POINTS_COUNT; i++) {
    KDTreeTestPoint * point = &test_points[i];
    kdtree_add(&kdtree, point->position, point);
  }
  assert(kdtree.count == KDTREE_TEST_POINTS_COUNT);
  kdtree_build(&kdtree);

  KDTreeTestPoint * item;
  item = (KDTreeTestPoint *)kdtree_find(&kdtree, (Vector){ 8.1, 0.9 });
  assert(item != NULL);
  assert(item->id == 6);

  item = (KDTreeTestPoint *)kdtree_find(&kdtree, (Vector){ 7.1, 1.9 });
  assert(item != NULL);
  assert(item->id == 1);

  item = (KDTreeTestPoint *)kdtree_find(&kdtree, (Vector){ 7.1, 3.1 });
  assert(item != NULL);
  assert(item->id == 7);

  item = (KDTreeTestPoint *)kdtree_find(&kdtree, (Vector){ 6.9, 3.1 });
  assert(item != NULL);
  assert(item->id == 8);

  kdtree_clear(&kdtree);
  assert(kdtree.count == 0);
  assert(kdtree.capacity >= KDTREE_TEST_POINTS_COUNT);

  kdtree_deinitialize(&kdtree);
  assert(kdtree.nodes == NULL);
  assert(kdtree.count == 0);
  assert(kdtree.capacity == 0);
}
