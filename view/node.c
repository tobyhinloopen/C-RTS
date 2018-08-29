#include "./node.h"
#include "string.h"

void node_initialize(Node * node) {
  vec_init(&node->children);
  node->frame = (Recti){ 0, 0, 0, 0 };
  string_assign_empty(&node->text_content);
  node->viewport_camera = (Vector3){ 0.0f, 0.0f, 0.0f };
  node->viewport_game = NULL;
  node->style.text_scale = 1.0f;
  node->style.background_color.value = 0x00000000;
  node->style.border_width = 0.0f;
  node->style.border_color.value = 0x00000000;
}

void node_deinitialize(Node * node) {
  vec_deinit(&node->children);
}
