#include "./node.h"
#include "string.h"

void node_initialize(Node * node) {
  memset(node, 0, sizeof(*node));
}

void node_deinitialize(Node * node) {
  vec_deinit(&node->children);
}
