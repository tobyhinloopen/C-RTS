#include "scalable_grid.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define PADDING 0.0001f
#define SIZE_MP (1.0f + PADDING * 2.0f)

void scalable_grid_initialize(ScalableGrid * sgrid) {
  grid_initialize(&sgrid->grid);
  sgrid->item_positions = NULL;
  sgrid->scale = (Vector){0, 0};
  sgrid->offset = (Vector){0, 0};
}

void scalable_grid_set_capacity(ScalableGrid * sgrid, unsigned int capacity) {
  grid_set_capacity(&sgrid->grid, capacity);
  sgrid->item_positions = realloc(sgrid->item_positions, sizeof(ItemPositionPair) * capacity);
  assert(sgrid->item_positions);
}

void scalable_grid_set_size(ScalableGrid * sgrid, GridXY size) {
  grid_set_size(&sgrid->grid, size);
}

void scalable_grid_set_transform(ScalableGrid * sgrid, Vector min, Vector max) {
  Vector size = (Vector){ max.x - min.x, max.y - min.y };

  sgrid->offset = (Vector){ min.x - size.x * PADDING, min.y - size.y * PADDING };
  sgrid->scale = (Vector){
    size.x * SIZE_MP / sgrid->grid.quick_access_size_x,
    size.y * SIZE_MP / sgrid->grid.quick_access_size_y
  };
}

void scalable_grid_clear(ScalableGrid * sgrid) {
  grid_clear(&sgrid->grid);
}

static GridXY vpos2gridxy(ScalableGrid * sgrid, Vector vpos) {
  return (GridXY) {
    (vpos.x - sgrid->offset.x) / sgrid->scale.x,
    (vpos.y - sgrid->offset.y) / sgrid->scale.y
  };
}

void scalable_grid_put(ScalableGrid * sgrid, Vector vpos, void * item) {
  Grid * grid = &sgrid->grid;
  // This pointer might point to an illegal position if items_count exceed the capacity. grid_put
  // uses assert to check the items_count against the capacity. When grid_put succeeds, the pointer
  // can be considered valid and it can have data assigned to it.
  ItemPositionPair * item_position_pair = &sgrid->item_positions[grid->items_count];
  grid_put(&sgrid->grid, vpos2gridxy(sgrid, vpos), item_position_pair);
  item_position_pair->item = item;
  item_position_pair->position = vpos;
}

typedef struct {
  Vector vpos;
  float max_distance;
  void * param;
  void (* callback)(void * item, float distance, void * param);
} ScalableGridIteratorContext;

static void scalable_grid_item_iterator(void * item_position_pair_ptr, void * context_ptr) {
  ScalableGridIteratorContext * context = (ScalableGridIteratorContext *)context_ptr;
  ItemPositionPair * item_position_pair = (ItemPositionPair *)item_position_pair_ptr;
  float distance = vector_distance(context->vpos, item_position_pair->position);
  if (distance <= context->max_distance) {
    context->callback(item_position_pair->item, distance, context->param);
  }
}

void scalable_grid_iterate_items(ScalableGrid * sgrid, Vector vpos, float max_distance, void * param, void (* callback)(void * item, float distance, void * param)) {
  GridXY min = vpos2gridxy(sgrid, (Vector){ vpos.x - max_distance, vpos.y - max_distance });
  GridXY max = vpos2gridxy(sgrid, (Vector){ vpos.x + max_distance, vpos.y + max_distance });
  ScalableGridIteratorContext context = {vpos, max_distance, param, callback};
  for (int x = min.x; x <= max.x; x++) {
    if (x >= 0 && x < sgrid->grid.quick_access_size_x) {
      for (int y = min.y; y <= max.y; y++) {
        if (y >= 0 && y < sgrid->grid.quick_access_size_y) {
          grid_iterate_items(&sgrid->grid, (GridXY){x, y}, &context, scalable_grid_item_iterator);
        }
      }
    }
  }
}

void scalable_grid_deinitialize(ScalableGrid * sgrid) {
  free(sgrid->item_positions);
  sgrid->item_positions = NULL;
  grid_deinitialize(&sgrid->grid);
}
