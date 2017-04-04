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

void kdtree_initialize(KDTree *);
void kdtree_set_capacity(KDTree *, size_t);
void kdtree_clear(KDTree *);
void kdtree_add(KDTree *, Vector, void *);
void kdtree_build(KDTree *);
void * kdtree_find(KDTree *, Vector);
void kdtree_deinitialize(KDTree *);

#endif
