#ifndef RENDERER_H
#define RENDERER_H

#include "vector.h"
#include "vector3.h"
#include <SDL2/SDL.h>
#include "opengl.h"

#define UNIT_VBO_BODY_LINE_COUNT (4)
#define UNIT_VBO_HEAD_LINE_COUNT (2)
#define UNIT_VBO_HEALTH_LINE_COUNT (1)
#define UNIT_VBO_VERTEX_COUNT ((UNIT_VBO_BODY_LINE_COUNT + UNIT_VBO_HEAD_LINE_COUNT + UNIT_VBO_HEALTH_LINE_COUNT) * 2)
#define UNIT_VBO_COUNT 4096

typedef union { Uint32 color; struct { Uint8 b; Uint8 g; Uint8 r; Uint8 a; }; } RendererColor;

typedef struct {
  RendererColor color;
  Vector vertex;
} RendererUnitVboElement;

typedef struct {
  SDL_Window * window;
  SDL_GLContext gl_context;
  int viewport_width;
  int viewport_height;
  Vector3 camera;
  Uint32 unit_color_data[UNIT_VBO_VERTEX_COUNT * UNIT_VBO_COUNT];
  Vector unit_vertex_data[UNIT_VBO_VERTEX_COUNT * UNIT_VBO_COUNT];
  int unit_vbo_length;
} Renderer;

#include "game.h"
#include "view/node.h"

void renderer_initialize(Renderer *);
void renderer_notify_viewport_resized(Renderer *);
Vector renderer_screen_to_world(const Renderer *, Vector);
Vector renderer_world_to_screen(const Renderer *, Vector);
void renderer_clear_color(const Renderer *, float r, float g, float b);
void renderer_begin(const Renderer *);
void renderer_render_map(const Renderer *, const Map *);
void renderer_render_world(Renderer *, World *);
void renderer_render_ui(const Renderer *, const Game *);
void renderer_render_view_node(const Renderer *, const Node *);
void renderer_present(const Renderer *);
void renderer_deinitialize(Renderer *);

#endif
