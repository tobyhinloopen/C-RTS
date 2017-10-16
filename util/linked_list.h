#ifndef UTIL_LINKED_LIST_H
#define UTIL_LINKED_LIST_H

#define LLI_CONTINUE 0
#define LLI_REMOVE 1
#define LLI_BREAK 2

struct _LLNode;

typedef struct _LLNode {
  void * value;
  struct _LLNode * next;
} LLNode;

typedef struct {
  LLNode * head;
} LinkedList;

void linked_list_initialize(LinkedList *);
void linked_list_push_front(LinkedList *, void *);
void linked_list_iterate(LinkedList *, int (*)(void *, void *), void *);
void linked_list_deinitialize(LinkedList *);

#endif
