#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include "renderer.h"
#include "world.h"
#include "projectile.h"
#include "pi.h"
#include "team_id.h"
#include "text_renderer.h"
#include "config.h"
#include "file.h"
#include "memory.h"

const float RAD2DEGf = 360 / PI2;

const int HALF_UNIT_TEXTURE_SIZE = 24;
const float PROJECTILE_LENGTH = 16.0f;
const float PROJECTILE_IMPACT_HALF_SIZE = 3.0f;
const int HEALTH_BAR_WIDTH = 32;
const int HEALTH_BAR_HEIGHT = 4;
const int HALF_FACTORY_TEXTURE_SIZE = 48;

#define UI_PADDING 128
#define MAP_PADDING 128

static SDL_Window * create_sdl_window() {
  SDL_Window * sdl_window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL|CONFIG_SDL_CREATE_WINDOW_FLAGS);
  assert(sdl_window);
  return sdl_window;
}

static GLuint create_shader(GLenum shaderType, const char * filename) {
  GLuint shader_id = glCreateShader(shaderType);

  File source;
  file_initialize(&source);
  file_read(&source, filename);
  glShaderSource(shader_id, 1, &source.data, &source.size);
  file_deinitialize(&source);

  assert(source.size < 1000);

  glCompileShader(shader_id);

  GLsizei info_log_length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    char * info_log = malloc(info_log_length);
    assert(info_log);
    printf("shader info log for %s\n", filename);
    glGetShaderInfoLog(shader_id, info_log_length, &info_log_length, info_log);
    printf("%.*s\n", info_log_length, info_log);
  }

  GLuint compile_status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_FALSE) {
    printf("compile_shader() failed for %s\n", filename);
    exit(1);
  }

  return shader_id;
}

static GLuint create_program() {
  GLuint vertex_shader_id = create_shader(GL_VERTEX_SHADER, "./renderer/test.vert");
  GLuint fragment_shader_id = create_shader(GL_FRAGMENT_SHADER, "./renderer/test.frag");

  GLuint program_id = glCreateProgram();

  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);

  GLsizei info_log_length;
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    char * info_log = malloc(info_log_length);
    assert(info_log);
    glGetProgramInfoLog(program_id, info_log_length, &info_log_length, info_log);
    printf("program link info log");
    printf("%.*s\n", info_log_length, info_log);
  }

  GLuint link_status;
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
  if (link_status == GL_FALSE) {
    printf("program link failed");
    exit(1);
  }

  glDetachShader(program_id, vertex_shader_id);
  glDetachShader(program_id, fragment_shader_id);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  return program_id;
}


// TRIANGLE
// This will identify our vertex buffer
GLuint vbo;
GLuint global_program_id;
static const GLfloat vertices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
};
// END TRIANGLE


void renderer_initialize(Renderer * renderer) {
  assert(sizeof(GLubyte) * 4 == sizeof(uint32_t));
  assert(sizeof(Vector) == 8);
  assert(sizeof(RendererColor) == 4);
  assert(sizeof(RendererUnitVboElement) == 12);

  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  renderer->window = create_sdl_window();
  renderer->gl_context = SDL_GL_CreateContext(renderer->window);

  // glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  // glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  // renderer_notify_viewport_resized(renderer);
  // renderer->camera = (Vector3) { INITIAL_CAMERA_X, INITIAL_CAMERA_Y, INITIAL_CAMERA_Z };

  GLuint program_id = 0;
  // GLuint program_id = create_program();
  // glUseProgram(program_id);

  // TRIANGLE
  global_program_id = program_id;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // END TRIANGLE
}

// void renderer_clear_color(const Renderer * renderer, float r, float g, float b) {
//   glClearColor(r, g, b, 1.0f);
//   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
// }

static float renderer_scale(const Renderer * renderer) {
  return 1.0f / (1.0f + renderer->camera.z);
}

// static void set_gl_team_color_alpha(int team_id, unsigned char alpha) {
//   RendererColor color = { TEAM_COLOR[team_id] };
//   glColor4ub(color.r, color.g, color.b, alpha);
// }

// static void set_gl_team_color(int team_id) {
//   set_gl_team_color_alpha(team_id, 255);
// }

// static void renderer_render_unit(Renderer * renderer, const Unit * unit) {
//   int index = renderer->unit_vbo_length++;
//   Uint32 * colors = &renderer->unit_color_data[index * UNIT_VBO_VERTEX_COUNT];
//   Color color = { value: TEAM_COLOR[unit->team_id] };
//   Uint32 colorCode = 0xFF000000 | (color.r << 16) | (color.g << 8) | color.b;
//   for (int i = 0; i < UNIT_VBO_VERTEX_COUNT; i++) {
//     colors[i] = colorCode;
//   }

//   Vector * vertices = &renderer->unit_vertex_data[index * UNIT_VBO_VERTEX_COUNT];

//   // body
//   Vector a = { -16.0f, -12.0f };
//   Vector b = { 16.0f, -12.0f };
//   Vector c = { 16.0f, 12.0f };
//   Vector d = { -16.0f, 12.0f };

//   // head
//   Vector e = { -4.0f, -8.0f };
//   Vector f = { 4.0f,  0.0f };
//   Vector g = { -4.0f,  8.0f };

//   // // health
//   Vector h = { -20.0f, -12.0f };
//   Vector i = { -20.0f, -12.0f };

//   float health = unit_health_percentage(unit);
//   const head_direction = unit->direction + unit->head_direction;

//   i.y += 24.0f * health;

//   vector_rotate(&a, unit->direction);
//   vector_rotate(&b, unit->direction);
//   vector_rotate(&c, unit->direction);
//   vector_rotate(&d, unit->direction);

//   vector_rotate(&h, unit->direction);
//   vector_rotate(&i, unit->direction);

//   vector_rotate(&e, head_direction);
//   vector_rotate(&f, head_direction);
//   vector_rotate(&g, head_direction);

//   vector_add(&a, unit->position);
//   vector_add(&b, unit->position);
//   vector_add(&c, unit->position);
//   vector_add(&d, unit->position);
//   vector_add(&e, unit->position);
//   vector_add(&f, unit->position);
//   vector_add(&g, unit->position);
//   vector_add(&h, unit->position);
//   vector_add(&i, unit->position);

//   vertices[ 0] = a;
//   vertices[ 1] = b;
//   vertices[ 2] = b;
//   vertices[ 3] = c;
//   vertices[ 4] = c;
//   vertices[ 5] = d;
//   vertices[ 6] = d;
//   vertices[ 7] = a;

//   vertices[ 8] = e;
//   vertices[ 9] = f;
//   vertices[10] = f;
//   vertices[11] = g;

//   vertices[12] = h;
//   vertices[13] = i;
// }

// static void renderer_render_projectile(const Renderer * renderer, const Projectile * projectile) {
//   set_gl_team_color_alpha(projectile->team_id,
//     (unsigned char)(projectile->decay_remaining / PROJECTILE_DECAY * 255.0f));

//   glPushMatrix();
//   glTranslatef(projectile->position.x, projectile->position.y, 0.1f);

//   if(projectile->distance_remaining > 0) {
//     glRotatef(projectile->direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);
//     glBegin(GL_LINES);

//     glVertex2f(0.0f, 0.0f);
//     glVertex2f(PROJECTILE_LENGTH, 0.0f);

//     glEnd();
//   } else {
//     glBegin(GL_LINES);

//     glVertex2f(-PROJECTILE_IMPACT_HALF_SIZE, -PROJECTILE_IMPACT_HALF_SIZE);
//     glVertex2f( PROJECTILE_IMPACT_HALF_SIZE,  PROJECTILE_IMPACT_HALF_SIZE);
//     glVertex2f( PROJECTILE_IMPACT_HALF_SIZE, -PROJECTILE_IMPACT_HALF_SIZE);
//     glVertex2f(-PROJECTILE_IMPACT_HALF_SIZE,  PROJECTILE_IMPACT_HALF_SIZE);

//     glEnd();
//   }

//   glPopMatrix();
// }

// static void renderer_render_factory(const Renderer * renderer, const Factory * factory) {
//   glPushMatrix();
//   glTranslatef(factory->position.x, factory->position.y, 0.0f);

//   set_gl_team_color(factory->team_id);

//   glRotatef(factory->direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);

//   glBegin(GL_LINE_LOOP);

//   glVertex2f(-28.0f, -24.0f);
//   glVertex2f( 28.0f, -24.0f);
//   glVertex2f( 28.0f, -18.0f);
//   glVertex2f(-22.0f, -18.0f);
//   glVertex2f(-22.0f,  18.0f);
//   glVertex2f( 28.0f,  18.0f);
//   glVertex2f( 28.0f,  24.0f);
//   glVertex2f(-28.0f,  24.0f);

//   glEnd();

//   float health = factory_health_percentage(factory);

//   glBegin(GL_LINES);

//   glVertex2f(-32.0f, -24.0f);
//   glVertex2f(-32.0f, -24.0f + 48.0f * health);

//   glEnd();

//   glBegin(GL_LINE_LOOP);

//   float build_percentage = factory_build_percentage(factory);

//   glVertex2f(-16.0f * build_percentage, -12.0f * build_percentage);
//   glVertex2f( 16.0f * build_percentage, -12.0f * build_percentage);
//   glVertex2f( 16.0f * build_percentage,  12.0f * build_percentage);
//   glVertex2f(-16.0f * build_percentage,  12.0f * build_percentage);

//   glEnd();

//   glPopMatrix();
// }

void renderer_notify_viewport_resized(Renderer * renderer) {
  // SDL_GetWindowSize(renderer->window, &renderer->viewport_width, &renderer->viewport_height);

  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();

  // double x = renderer->viewport_width/2;
  // double y = renderer->viewport_height/2;
  // glOrtho(-x, x, -y, y, -1.0f, 1.0f);
}


Vector renderer_screen_to_world(const Renderer * renderer, Vector point) {
  const float scale = renderer_scale(renderer);
  return (Vector) {
    (point.x - renderer->viewport_width/2) / scale + renderer->camera.x,
    (point.y - renderer->viewport_height/2) / -scale + renderer->camera.y
  };
}

Vector renderer_world_to_screen(const Renderer * renderer, Vector position) {
  const float scale = renderer_scale(renderer);
  return (Vector) {
    (position.x - renderer->camera.x) * scale + renderer->viewport_width/2,
    (position.y - renderer->camera.y) * -scale + renderer->viewport_height/2
  };
}

// static int is_vector_in_viewport(const Renderer * renderer, Vector vector, int padding) {
//   Vector point = renderer_world_to_screen(renderer, vector);
//   return point.x + padding >= 0.0f && point.y + padding >= 0.0f
//     && point.x - padding <= renderer->viewport_width
//     && point.y - padding <= renderer->viewport_height;
// }

// static void render_unit_entity(Entity * entity, void * renderer_ptr) {
//   Renderer * renderer = (Renderer *)renderer_ptr;
//   if(is_vector_in_viewport(renderer, entity->unit.position, HALF_UNIT_TEXTURE_SIZE))
//     renderer_render_unit(renderer, &entity->unit);
// }

// static void render_factory_entity(Entity * entity, void * renderer_ptr) {
//   const Renderer * renderer = (const Renderer *)renderer_ptr;
//   if(is_vector_in_viewport(renderer, entity->factory.position, HALF_FACTORY_TEXTURE_SIZE))
//     renderer_render_factory(renderer, &entity->factory);
// }

// static void render_projectile_entity(Entity * entity, void * renderer_ptr) {
//   const Renderer * renderer = (const Renderer *)renderer_ptr;
//   if(is_vector_in_viewport(renderer, entity->projectile.position, PROJECTILE_LENGTH))
//     renderer_render_projectile(renderer, &entity->projectile);
// }

void renderer_begin(const Renderer * renderer) {
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
}

// void renderer_render_map(const Renderer * renderer, const  Map * map) {
//   glPushMatrix();
//   glTranslatef(0.0f, 0.0f, -1.0f);

//   // map padding
//   glColor3f(0.95f, 0.95f, 0.95f);
//   glTranslatef(0.0f, 0.0f, 0.1);

//   glBegin(GL_QUADS);

//   glVertex2f(-MAP_PADDING, -MAP_PADDING);
//   glVertex2f(map->size.x + MAP_PADDING, - MAP_PADDING);
//   glVertex2f(map->size.x + MAP_PADDING, map->size.y + MAP_PADDING);
//   glVertex2f(-MAP_PADDING, map->size.y + MAP_PADDING);

//   glEnd();

//   // map background
//   glColor3f(1.0f, 1.0f, 1.0f);
//   glTranslatef(0.0f, 0.0f, 0.1);

//   glBegin(GL_QUADS);

//   glVertex2f(0, 0);
//   glVertex2f(map->size.x, 0);
//   glVertex2f(map->size.x, map->size.y);
//   glVertex2f(0, map->size.y);

//   glEnd();

//   // map inner border
//   glColor3f(0.8f, 0.8f, 0.8f);
//   glTranslatef(0.0f, 0.0f, 0.1);

//   glBegin(GL_LINE_LOOP);

//   glVertex2f(0, 0);
//   glVertex2f(map->size.x, 0);
//   glVertex2f(map->size.x, map->size.y);
//   glVertex2f(0, map->size.y);

//   glEnd();

//   // map outer border
//   glBegin(GL_LINE_LOOP);

//   glVertex2f(-MAP_PADDING, -MAP_PADDING);
//   glVertex2f(map->size.x + MAP_PADDING, - MAP_PADDING);
//   glVertex2f(map->size.x + MAP_PADDING, map->size.y + MAP_PADDING);
//   glVertex2f(-MAP_PADDING, map->size.y + MAP_PADDING);

//   glEnd();

//   glPopMatrix();
// }

// static void render_units(Renderer * renderer, World * world) {
//   renderer->unit_vbo_length = 0;
//   world_pool_iterate_entities(&world->units, renderer, render_unit_entity);

//   if (renderer->unit_vbo_length > 0) {
//     glEnableClientState(GL_VERTEX_ARRAY);
//     glEnableClientState(GL_COLOR_ARRAY);
//     glColorPointer(4, GL_UNSIGNED_BYTE, 0, &renderer->unit_color_data);
//     glVertexPointer(2, GL_FLOAT, 0, &renderer->unit_vertex_data);
//     glDrawArrays(GL_LINES, 0, renderer->unit_vbo_length * UNIT_VBO_VERTEX_COUNT);
//     glDisableClientState(GL_VERTEX_ARRAY);
//     glDisableClientState(GL_COLOR_ARRAY);
//   }
// }

// void renderer_render_world(Renderer * renderer, World * world) {
//   render_units(renderer, world);
//   world_pool_iterate_entities(&world->factories, renderer, render_factory_entity);
//   world_pool_iterate_entities(&world->projectiles, renderer, render_projectile_entity);
// }

// static void ui_align(const Renderer * renderer, float x, float y, float scale) {
//   glLoadIdentity();
//   glTranslatef(
//     (renderer->viewport_width - UI_PADDING) * x / 2,
//     (renderer->viewport_height - UI_PADDING) * -y / 2,
//     1.0f
//   );
//   glScalef(scale, scale, scale);
// }

// static clock_t duration_avg(const clock_t * durations, int duration_count) {
//   clock_t sum = 0;
//   for (int i = 0; i < duration_count; i++)
//     sum += durations[i];
//   return sum / duration_count;
// }

// typedef struct {
//   GameModule * mod;
//   clock_t duration;
// } ModulePerformance;

// static int compare_module_performances(const void * a, const void * b) {
//   clock_t duration_a = ((ModulePerformance *)a)->duration;
//   clock_t duration_b = ((ModulePerformance *)b)->duration;
//   if (duration_a < duration_b) return 1;
//   if (duration_a > duration_b) return -1;
//   return 0;
// }

// static void render_ui_debug(const Renderer * renderer, const Game * game) {
//   ui_align(renderer, -1, -1, 0.8);
//   char debug_str[2048];
//   int length = snprintf(debug_str, sizeof(debug_str),
//     "%.0f, %.0f %.0f%%; CMDPOS: %.0f, %.0f\n%22s:%7i\n%22s:%7i\n%22s:%7i\n%22s:%7i 0x%08x\n%22s:%7lu  fps%6.1f\n",
//     renderer->camera.x,
//     renderer->camera.y,
//     renderer_scale(renderer) * 100,
//     game->command_position.x,
//     game->command_position.y,
//     "factories", game->world.factories.entity_count,
//     "units", game->world.units.entity_count,
//     "projectiles", game->world.projectiles.entity_count,
//     "time", game->current_time - game->start_time, game->current_time - game->start_time,
//     "update realtime ms",
//     (game->cumulative_update_duration * 1000 / CLOCKS_PER_SEC),
//     game->update_count * CLOCKS_PER_SEC * 1.0f / game->cumulative_update_duration
//   );

//   const int modcount = game->modules_count;
//   ModulePerformance mod_performances[modcount];

//   for (int i = 0; i < modcount; i++) {
//     ModulePerformance * perf = &mod_performances[i];
//     perf->mod = &game->modules[i];
//     perf->duration = duration_avg(perf->mod->duration_update, GAME_MODULE_DURATION_LENGTH);
//   }

//   qsort(mod_performances, modcount, sizeof(ModulePerformance), compare_module_performances);

//   for (int i = 0; i < modcount; i++) {
//     ModulePerformance * perf = &mod_performances[i];
//     length += snprintf(
//       debug_str + length,
//       sizeof(debug_str) - length,
//       "%22s:%7luC log2%5.1f\n",
//       perf->mod->name + 4,
//       perf->duration, perf->duration ? log2f(perf->duration) : 0);
//   }

//   text_renderer_render_string(debug_str, length);
// }

// void renderer_render_ui(const Renderer * renderer, const Game * game) {
//   glMatrixMode(GL_MODELVIEW);
//   glColor3f(0.4f, 0.4f, 0.4f);
//   render_ui_debug(renderer, game);
// }

// static void set_color(Color color) {
//   glColor4ubv((GLubyte*)&color.value);
// }

// static void render_view_node_frame(const Renderer * renderer, const Node * node) {
//   const Recti frame = node->frame;
//   const NodeStyle style = node->style;
//   const int l = frame.x;
//   const int t = frame.y;
//   const int r = frame.x + frame.w;
//   const int b = frame.y + frame.h;

//   if (style.background_color.value) {
//     set_color(style.background_color);

//     glBegin(GL_QUADS);
//     glVertex2i(l, t);
//     glVertex2i(r, t);
//     glVertex2i(r, b);
//     glVertex2i(l, b);
//     glEnd();
//   }

//   if (style.border_width && style.border_color.value) {
//     set_color(style.border_color);
//     glLineWidth(style.border_width);

//     glBegin(GL_LINE_LOOP);
//     glVertex2i(l, t);
//     glVertex2i(r, t);
//     glVertex2i(r, b);
//     glVertex2i(l, b);
//     glEnd();
//   }
// }

// static void render_view_node_children(const Renderer * renderer, const Node * node) {
//   Node * child;
//   int i;
//   vec_foreach_ptr(&node->children, child, i) {
//     renderer_render_view_node(renderer, child);
//   }
// }

// static void renderer_begin_world(const Renderer * renderer) {
//   glLoadIdentity();
//   const float scale = renderer_scale(renderer);
//   glScalef(scale, scale, 1.0f);
//   glTranslatef(-renderer->camera.x, -renderer->camera.y, 0.0f);
//   renderer_clear_color(renderer, 0.9f, 0.9f, 0.9f);
// }

// static void render_view_node_viewport(const Renderer * renderer, const Node * node) {
//   if (node->viewport_game) {
//     Renderer renderer_copy = *renderer;
//     renderer_copy.camera = node->viewport_camera;
//     Game * game = node->viewport_game;

//     renderer_begin_world(&renderer_copy);
//     renderer_render_map(&renderer_copy, &game->map);
//     renderer_render_world(&renderer_copy, &game->world);
//     renderer_render_ui(&renderer_copy, game);
//   }
// }

// static void render_view_node_text(const Renderer * renderer, const Node * node) {
//   text_renderer_render_string(node->text_content.data, node->text_content.length);
// }


void renderer_render_view_node(const Renderer * renderer, const Node * node) {
  // glPushMatrix();
  // ui_align(renderer, -1, -1, 1);

  // render_view_node_frame(renderer, node);
  // render_view_node_viewport(renderer, node);

  // ui_align(renderer, -1, -1, node->style.text_scale);
  // render_view_node_text(renderer, node);

  // render_view_node_children(renderer, node);

  // glPopMatrix();

  // RENDER TRIANGLE

  // 1st attribute buffer : vertices
  glLoadIdentity();
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glUseProgram(global_program_id);
  glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  GLint position_attribute = glGetAttribLocation(global_program_id, "position");
  glEnableVertexAttribArray(position_attribute);
  glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(-0.5f, -0.5f);
  glEnd();
  // glDisableVertexAttribArray(0);

  // END TRIANGLE
}

void renderer_present(const Renderer * renderer) {
  SDL_GL_SwapWindow(renderer->window);
}

void renderer_deinitialize(Renderer * renderer) {
  SDL_GL_DeleteContext(renderer->gl_context);
  SDL_DestroyWindow(renderer->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
