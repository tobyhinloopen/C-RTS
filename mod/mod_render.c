#include "mod_render.h"

#include "../view/node.h"
#include "../renderer.h"
#include "../camera.h"

static void resize_frame(Node * node, Renderer * renderer) {
  node->frame.x = 0;
  node->frame.y = 0;
  node->frame.w = renderer->viewport_width;
  node->frame.h = renderer->viewport_height;
}

static void mod_render_initialize(Game * game) {
  renderer_initialize(&game->renderer);
  resize_frame(game->node, &game->renderer);
  Node label_node;
  node_initialize(&label_node);
  label_node.style.text_scale = 0.9f;
  string_assign_constant_cstring(&label_node.text_content, "Hello");

  vec_push(&game->node->children, label_node);
}

static void handle_window_resize(Game * game) {
  if(game->is_window_resized) {
    renderer_notify_viewport_resized(&game->renderer);
    resize_frame(game->node, &game->renderer);
    game->is_window_resized = 0;
  }
}

static void mod_render_update(Game * game, unsigned int delta_i) {
  handle_window_resize(game);
  game->node->viewport_camera = game->renderer.camera;
  renderer_begin(&game->renderer);
  renderer_render_view_node(&game->renderer, game->node);
  renderer_present(&game->renderer);
}

static void mod_render_deinitialize(Game * game) {
  renderer_deinitialize(&game->renderer);
}

void mod_render(GameModule * mod) {
  mod->initialize = mod_render_initialize;
  mod->update = mod_render_update;
  mod->deinitialize = mod_render_deinitialize;
}
