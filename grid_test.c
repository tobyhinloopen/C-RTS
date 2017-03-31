#include "grid_test.h"
#include "grid.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

unsigned int assert_int_44_count = 0;

static void assert_int_44(void * item_ptr, void * _param) {
  int * item = (int *)item_ptr;
  assert(*item == 44);
  assert_int_44_count++;
}

void test_grid() {
  Grid grid;

  grid_initialize(&grid);
  grid_set_size(&grid, (GridXY){ 16, 16 });
  grid_set_capacity(&grid, 16);
  grid_clear(&grid);

  int item = 44;
  grid_put(&grid, (GridXY){ 8, 8 }, &item);
  grid_put(&grid, (GridXY){ 8, 8 }, &item);
  grid_iterate_items(&grid, (GridXY){ 8, 8 }, NULL, assert_int_44);
  assert(assert_int_44_count == 2);

  grid_iterate_items(&grid, (GridXY){ 7, 8 }, NULL, assert_int_44);
  assert(assert_int_44_count == 2);

  grid_deinitialize(&grid);
}
