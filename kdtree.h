#ifndef KDTREE_H
#define KDTREE_H

#include "vector.h"
#include <stdlib.h>

typedef struct {
  void * ref;
  Vector position;
} KDTreeItem;

typedef struct KDTreeNode KDTreeNode;

struct KDTreeNode {
  KDTreeItem item;
  KDTreeNode * left;
  KDTreeNode * right;
};

typedef struct {
  size_t capacity;
  size_t count;
  KDTreeItem * items;
  KDTreeNode * nodes;
} KDTree;

typedef struct {
  void * ref;
  float distance;
} KDTreeFindResult;

void kdtree_initialize(KDTree *);
void kdtree_set_capacity(KDTree *, size_t);
void kdtree_clear(KDTree *);
void kdtree_add(KDTree *, Vector, void *);
void kdtree_build(KDTree *);
void * kdtree_find(KDTree *, Vector);
KDTreeFindResult kdtree_find_distance_excluding(KDTree *, Vector, void * excluding_ref);
KDTreeFindResult kdtree_find_distance(KDTree *, Vector);
void kdtree_debug_print(KDTree *, void * param, void (* print_fn)(void * ref, void * param)) ;
void kdtree_deinitialize(KDTree *);

#endif
