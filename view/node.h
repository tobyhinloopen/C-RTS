#ifndef VIEW_NODE_H
#define VIEW_NODE_H

#include "../vector3.h"
#include "../game.h"
#include "../util/rect.h"
#include "../util/color.h"
#include "../util/string.h"
#include "../vendor/vec.h"

typedef struct {
  Color background_color;
  Color border_color;
  float border_width;
} NodeStyle;

typedef struct Node Node;

struct Node {
  vec_t(Node) children;
  Recti frame;
  NodeStyle style;
  String text_content;
  Vector3 viewport_camera;
  Game * viewport_game;
};

void node_initialize(Node * node);
void node_deinitialize(Node * node);

#endif
