#ifndef BKTREE_H
#define BKTREE_H

#include "limits.h"

#define BKTREE_SCALAR_MAX USHRT_MAX
#define BKTREE_VALUE_MAX USHRT_MAX
#define BKTREE_DISTANCE_MAX UINT_MAX

typedef unsigned short BKValue;
typedef unsigned int BKSize;
typedef unsigned int BKDistance;
typedef unsigned short BKScalar;
typedef unsigned char BKBool;

typedef struct {
  BKBool leaf;
  BKScalar x;
  BKScalar y;
  BKValue value;
} BKNode;

typedef struct {
  BKNode * nodes;
  BKSize depth;
  BKSize count;
  BKSize capacity;
} BKTree;

typedef struct {
  BKValue value;
  BKDistance distance_sq;
} BKResult;

void bktree_initialize(BKTree * tree);

// increases or decreases the capacity to be able to store at least `n` nodes
// the new capacity will be greater or equal to `n`
void bktree_build(BKTree * tree, BKNode * nodes, BKSize n);

// find up to `n` closest nodes within `max_distance` of point `x`,`y`. The amount of nodes found is
// returned.
BKSize bktree_find(BKTree * tree, BKScalar x, BKScalar y, BKResult * results, BKSize n, BKDistance max_distance_sq);

// find the closest node for `p`
BKResult bktree_first(BKTree * tree, BKScalar x, BKScalar y);

void bktree_deinitialize(BKTree * tree);

#endif
