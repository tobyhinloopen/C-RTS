#ifndef SCALABLE_GRID_H
#define SCALABLE_GRID_H

#include "grid.h"
#include "vector.h"

/**
This is an encapsulation of the generic grid that includes transforming floating point coordinates
to grid coordinates. The position where the item was inserted is also stored.

This scalable grid allows iteration of items within a certain floating-point distance without
concerning about the actual grid layout. It can further optimize iteration and it can do sorted
iteration of results.
*/

typedef struct {
  void * item;
  Vector position;
} ItemPositionPair;

typedef struct {
  Grid grid;
  ItemPositionPair * item_positions;
  Vector scale;
  Vector offset;
} ScalableGrid;

// Initializes a grid of size 0x0 with 0 capacity. Set a size, transform & capacity before using it.
void scalable_grid_initialize(ScalableGrid *);

// Set the capacity of the underlying grid & item positions.
void scalable_grid_set_capacity(ScalableGrid *, unsigned int);

// Apply grid_set_size on the grid
void scalable_grid_set_size(ScalableGrid *, GridXY);

// Set the transformation scale & offset based on a minimum & maximum position
void scalable_grid_set_transform(ScalableGrid *, Vector min, Vector max);

// Apply grid_clear on the grid
void scalable_grid_clear(ScalableGrid *);

// Store an item referenced by pointer at a given coordinate
void scalable_grid_put(ScalableGrid *, Vector, void *);

// Iterate all items that are within a given distance from a given coordinate.
void scalable_grid_iterate_items(ScalableGrid *, Vector position, float max_distance, void * param, void (*)(void * item, float distance, void * param));

// Deinitialize the scalable grid and its underlying grid.
void scalable_grid_deinitialize(ScalableGrid *);

#endif
