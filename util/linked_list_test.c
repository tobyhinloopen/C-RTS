#include "linked_list_test.h"
#include "linked_list.h"
#include <assert.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} Thing;

static int thing_sum_func(void * thing_ptr, void * thing_sum_ptr) {
  Thing * thing = (Thing *)thing_ptr;
  Thing * thing_sum = (Thing *)thing_sum_ptr;
  thing_sum->x += thing->x;
  thing_sum->y += thing->y;
  return 0;
}

static int thing_delete_negative_x(void * thing_ptr, void * _) {
  Thing * thing = (Thing *)thing_ptr;
  return thing->x < 0 ? LLI_REMOVE : 0;
}

void test_linked_list() {
  LinkedList list;
  linked_list_initialize(&list);
  Thing a = {-1, 2};
  linked_list_push_front(&list, &a);
  Thing b = {1, 2};
  linked_list_push_front(&list, &b);
  Thing c = {3, 4};
  linked_list_push_front(&list, &c);
  Thing sum = {0, 0};
  linked_list_iterate(&list, thing_sum_func, &sum);
  assert(sum.x == a.x + b.x + c.x);
  assert(sum.y == a.y + b.y + c.y);
  linked_list_iterate(&list, thing_delete_negative_x, NULL);
  sum.x = 0;
  sum.y = 0;
  linked_list_iterate(&list, thing_sum_func, &sum);
  assert(sum.x == b.x + c.x);
  assert(sum.y == b.y + c.y);
}
