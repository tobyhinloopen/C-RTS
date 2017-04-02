#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

void grid_initialize(Grid * grid) {
  grid->items_capacity = 0;
  grid->items_count = 0;
  grid->items = NULL;
  grid->quick_access_size_x = 0;
  grid->quick_access_size_y = 0;
  grid->quick_access_list = NULL;
}

static size_t quick_access_list_byte_size(Grid * grid) {
  return sizeof(GridItem *) * grid->quick_access_size_x * grid->quick_access_size_y;
}

void grid_set_size(Grid * grid, GridXY size) {
  grid->quick_access_size_x = size.x;
  grid->quick_access_size_y = size.y;
  grid->quick_access_list = realloc(grid->quick_access_list, quick_access_list_byte_size(grid));
  assert(grid->quick_access_list);
}

void grid_set_capacity(Grid * grid, unsigned int capacity) {
  grid->items = realloc(grid->items, sizeof(GridItem) * capacity);
  assert(grid->items);
  grid->items_capacity = capacity;
}

void grid_clear(Grid * grid) {
  assert(NULL == 0);
  memset(grid->quick_access_list, 0, quick_access_list_byte_size(grid));
  grid->items_count = 0;
}

static GridItem ** grid_get_ptr(Grid * grid, GridXY pos) {
#ifndef NDEBUG
  if(pos.x < 0 || pos.y < 0 || pos.x >= grid->quick_access_size_x || pos.y >= grid->quick_access_size_y) {
    printf("Tried to access pos %i,%i while grid is limited to %i,%i\n", pos.x, pos.y, grid->quick_access_size_x, grid->quick_access_size_y);
    assert(0);
  }
#endif
  return &grid->quick_access_list[pos.y * grid->quick_access_size_x + pos.x];
}

void grid_put(Grid * grid, GridXY pos, void * item) {
  assert(grid->items_count < grid->items_capacity);

  GridItem ** quick_access_ptr = grid_get_ptr(grid, pos);
  GridItem * new_item_ptr = &grid->items[grid->items_count++];
  new_item_ptr->item = item;
  new_item_ptr->next = quick_access_ptr == NULL ? NULL : *quick_access_ptr;
  *quick_access_ptr = new_item_ptr;
}

void grid_iterate_items(Grid * grid, GridXY pos, void * param, void (* callback)(void * item, void * param)) {
  GridItem * grid_item = *grid_get_ptr(grid, pos);
  while(grid_item != NULL) {
    void * item = grid_item->item;
    grid_item = grid_item->next;
    callback(item, param);
  }
}

void grid_deinitialize(Grid * grid) {
  free(grid->items);
  free(grid->quick_access_list);
}
