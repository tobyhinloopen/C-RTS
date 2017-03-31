#ifndef GRID_H
#define GRID_H

/**
The grid is designed to be able to quickly access items by their approximate position. This is done
by deviding all possible position within a space into rectangles. Every rectangle contains a
reference to the first item of a linked-list of all items in that square (or NULL if the square is
empty)

The grid-related functions accept float coordinates. These coordinates are transformed by scale and
offset. Flooring the resulting coordinate is the destination square.
*/

typedef struct GridItem GridItem;

struct GridItem {
  void * item;
  GridItem * next;
};

typedef struct {
  unsigned int items_capacity;
  unsigned int items_count;
  GridItem * items;
  unsigned int quick_access_size_x;
  unsigned int quick_access_size_y;
  GridItem ** quick_access_list;
} Grid;

typedef struct {
  unsigned int x;
  unsigned int y;
} GridXY;

// Initializes a grid of size 0x0 with 0 capacity. Set a size, transform & capacity before using it.
void grid_initialize(Grid *);

// Resize the grid. This resizes the allocated memory. This silently invalidates the grid content.
// (IE if you try to access previously inserted data, you'll get garbage)
void grid_set_size(Grid *, GridXY);

// Set the maximum amount of grid item for this grid. This resizes the allocated memory.
// (IE if you try to access previously inserted data, you'll get garbage)
void grid_set_capacity(Grid *, unsigned int);

// Clear the grid by setting the items-count to 0, and clearing the quick access list to all-NULL.
void grid_clear(Grid *);

// Store an item referenced by pointer at a given grid coordinate.
void grid_put(Grid *, GridXY, void *);

// Iterate all items at a given grid coordinate. This method is fairly cheap since it iterates a
// single linked list.
void grid_iterate_items(Grid *, GridXY, void * param, void (*)(void * item, void * param));

void grid_deinitialize(Grid *);

#endif
