#include "linked_list.h"

#include "stdlib.h"
#include "assert.h"

void linked_list_initialize(LinkedList * list) {
  list->head = NULL;
}

void linked_list_push_front(LinkedList * list, void * value) {
  LLNode * node = (LLNode *)malloc(sizeof(LLNode));
  assert(node);
  node->next = list->head;
  node->value = value;
  list->head = node;
}

void linked_list_iterate(LinkedList * list, int (* func)(void * value, void * arg), void * arg) {
  LLNode * curr = list->head;
  LLNode * prev = NULL;
  while(curr) {
    int func_result = func(curr->value, arg);
    LLNode * next = curr->next;
    if(func_result & LLI_REMOVE) {
      if(prev) {
        prev->next = next;
      } else {
        list->head = next;
      }
      free(curr);
    } else {
      prev = curr;
    }
    if (func_result & LLI_BREAK) {
      return;
    }
    curr = next;
  }
}

void linked_list_deinitialize(LinkedList * list) {
  LLNode * curr = list->head;
  while(curr) {
    LLNode * next = curr->next;
    free(curr);
    curr = next;
  }
  list->head = NULL;
}
