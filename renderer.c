#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include "renderer.h"
#include "world.h"
#include "projectile.h"
#include "pi.h"
#include "team_id.h"

const float RAD2DEGf = 360 / PI2;

const int INITIAL_WINDOW_WIDTH = 960;
const int INITIAL_WINDOW_HEIGHT = 540;

const int HALF_UNIT_TEXTURE_SIZE = 24;
const float PROJECTILE_LENGTH = 16.0f;
const float PROJECTILE_IMPACT_HALF_SIZE = 3.0f;
const int HEALTH_BAR_WIDTH = 32;
const int HEALTH_BAR_HEIGHT = 4;
const int HALF_FACTORY_TEXTURE_SIZE = 48;

typedef union { Uint32 color; struct { Uint8 b; Uint8 g; Uint8 r; }; } RendererColor;

static SDL_Window * create_sdl_window() {
  SDL_Window * sdl_window = SDL_CreateWindow("SDL Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_OPENGL);
  assert(sdl_window);
  return sdl_window;
}

void renderer_initialize(Renderer * renderer) {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  renderer->window = create_sdl_window();
  renderer->gl_context = SDL_GL_CreateContext(renderer->window);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  renderer_notify_viewport_resized(renderer);
  renderer->camera = (Vector3) { 0.0f, 0.0f, 2.0f };
}

void renderer_clear_color(Renderer * renderer, float r, float g, float b) {
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

static float renderer_scale(Renderer * renderer) {
  return 1.0f / (1.0f + renderer->camera.z);
}

static void set_gl_team_color_alpha(int team_id, unsigned char alpha) {
  RendererColor color = { TEAM_COLOR[team_id] };
  glColor4ub(color.r, color.g, color.b, alpha);
}

static void set_gl_team_color(int team_id) {
  set_gl_team_color_alpha(team_id, 255);
}

static void renderer_render_unit(Renderer * renderer, Unit * unit) {
  glPushMatrix();
  glTranslatef(unit->position.x, unit->position.y, 0.0f);

  set_gl_team_color(unit->team_id);

  glRotatef(unit->direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);

  glBegin(GL_LINE_LOOP);

  glVertex2f(-16.0f, -12.0f);
  glVertex2f( 16.0f, -12.0f);
  glVertex2f( 16.0f,  12.0f);
  glVertex2f(-16.0f,  12.0f);

  glEnd();

  float health = unit_health_percentage(unit);

  glBegin(GL_LINES);

  glVertex2f(-20.0f, -12.0f);
  glVertex2f(-20.0f, -12.0f + 24.0f * health);

  glEnd();

  glRotatef(unit->head_direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);

  glBegin(GL_LINE_STRIP);

  glVertex2f(-4.0f, -8.0f);
  glVertex2f( 4.0f,  0.0f);
  glVertex2f(-4.0f,  8.0f);

  glEnd();
  glPopMatrix();
}

static void renderer_render_projectile(Renderer * renderer, Projectile * projectile) {
  set_gl_team_color_alpha(projectile->team_id,
    (unsigned char)(projectile->decay_remaining / PROJECTILE_DECAY * 255.0f));

  glPushMatrix();
  glTranslatef(projectile->position.x, projectile->position.y, 0.1f);

  if(projectile->distance_remaining > 0) {
    glRotatef(projectile->direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(PROJECTILE_LENGTH, 0.0f);

    glEnd();
  } else {
    glBegin(GL_LINES);

    glVertex2f(-PROJECTILE_IMPACT_HALF_SIZE, -PROJECTILE_IMPACT_HALF_SIZE);
    glVertex2f( PROJECTILE_IMPACT_HALF_SIZE,  PROJECTILE_IMPACT_HALF_SIZE);
    glVertex2f( PROJECTILE_IMPACT_HALF_SIZE, -PROJECTILE_IMPACT_HALF_SIZE);
    glVertex2f(-PROJECTILE_IMPACT_HALF_SIZE,  PROJECTILE_IMPACT_HALF_SIZE);

    glEnd();
  }

  glPopMatrix();
}

static void renderer_render_factory(Renderer * renderer, Factory * factory) {
  glPushMatrix();
  glTranslatef(factory->position.x, factory->position.y, 0.0f);

  set_gl_team_color(factory->team_id);

  glRotatef(factory->direction * RAD2DEGf, 0.0f, 0.0f, 1.0f);

  glBegin(GL_LINE_LOOP);

  glVertex2f(-28.0f, -24.0f);
  glVertex2f( 28.0f, -24.0f);
  glVertex2f( 28.0f, -18.0f);
  glVertex2f(-22.0f, -18.0f);
  glVertex2f(-22.0f,  18.0f);
  glVertex2f( 28.0f,  18.0f);
  glVertex2f( 28.0f,  24.0f);
  glVertex2f(-28.0f,  24.0f);

  glEnd();

  float health = factory_health_percentage(factory);

  glBegin(GL_LINES);

  glVertex2f(-32.0f, -24.0f);
  glVertex2f(-32.0f, -24.0f + 48.0f * health);

  glEnd();

  glBegin(GL_LINE_LOOP);

  float build_percentage = factory_build_percentage(factory);

  glVertex2f(-16.0f * build_percentage, -12.0f * build_percentage);
  glVertex2f( 16.0f * build_percentage, -12.0f * build_percentage);
  glVertex2f( 16.0f * build_percentage,  12.0f * build_percentage);
  glVertex2f(-16.0f * build_percentage,  12.0f * build_percentage);

  glEnd();

  glPopMatrix();
}

void renderer_notify_viewport_resized(Renderer * renderer) {
  SDL_GL_GetDrawableSize(renderer->window, &renderer->viewport_width, &renderer->viewport_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double x = renderer->viewport_width/2;
  double y = renderer->viewport_height/2;
  glOrtho(-x, x, -y, y, -1.0f, 1.0f);
}


Vector renderer_screen_to_world(Renderer * renderer, Vector point) {
  const float scale = renderer_scale(renderer);
  return (Vector) {
    (point.x - renderer->viewport_width/2) / scale + renderer->camera.x,
    (point.y - renderer->viewport_height/2) / scale + renderer->camera.y
  };
}

Vector renderer_world_to_screen(Renderer * renderer, Vector position) {
  const float scale = renderer_scale(renderer);
  return (Vector) {
    (position.x - renderer->camera.x) * scale + renderer->viewport_width/2,
    (position.y - renderer->camera.y) * scale + renderer->viewport_height/2
  };
}

static int is_vector_in_viewport(Renderer * renderer, Vector vector, int padding) {
  Vector point = renderer_world_to_screen(renderer, vector);
  return point.x + padding >= 0.0f && point.y + padding >= 0.0f
    && point.x - padding <= renderer->viewport_width
    && point.y - padding <= renderer->viewport_height;
}

static void render_entity(Entity * entity, void * renderer_ptr) {
  Renderer * renderer = (Renderer *)renderer_ptr;
  switch(entity->type) {
    case UNIT:
      if(is_vector_in_viewport(renderer, entity->unit.position, HALF_UNIT_TEXTURE_SIZE))
        renderer_render_unit(renderer, &entity->unit);
      break;
    case PROJECTILE:
      if(is_vector_in_viewport(renderer, entity->projectile.position, PROJECTILE_LENGTH))
        renderer_render_projectile(renderer, &entity->projectile);
      break;
    case FACTORY:
      if(is_vector_in_viewport(renderer, entity->factory.position, HALF_FACTORY_TEXTURE_SIZE))
        renderer_render_factory(renderer, &entity->factory);
      break;
    case NONE: break;
  }
}

void renderer_render_world(Renderer * renderer, World * world) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  const float scale = renderer_scale(renderer);
  glScalef(scale, scale, 1.0f);
  glTranslatef(-renderer->camera.x, -renderer->camera.y, 0.0f);

  world_iterate_entities(world, renderer, render_entity);
}

void renderer_present(Renderer * renderer) {
  SDL_GL_SwapWindow(renderer->window);
}

void renderer_deinitialize(Renderer * renderer) {
  SDL_GL_DeleteContext(renderer->gl_context);
  SDL_DestroyWindow(renderer->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
