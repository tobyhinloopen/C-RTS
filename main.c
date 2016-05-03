#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "unit.h"
#include "projectile.h"
#include "renderer.h"
#include "test.h"
#include "world.h"
#include "pi.h"
#include "vector.h"
#include "unit/behavior.h"
#include <math.h>

const int TEAM_COUNT = 4;
const int TEAM_COLOR[TEAM_COUNT] = { 0xFF0000, 0x00CC00, 0x4444FF, 0xCC8800 };

const int UNIT_SPAWN_INTERVAL_MS = 20;
const int UNIT_SPAWN_MAX_GROUP_SIZE = 8;
const int UNIT_MAX_SPAWN_COUNT = 400;
const float CAMERA_SPEED = 512.0f;
const float CAMERA_ZOOM_SPEED = 0.5f;

typedef struct {
  Vector position;
  float zoom;
} CameraMovement;

static void update_unit_behavior(Unit * unit, void * world_ptr) {
  World * world = (World*)world_ptr;
  Unit * closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world);
  Unit * closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f);

  float unit_health = unit_health_percentage(unit);

  if(closest_friendly_unit != NULL)
    unit_behavior_move_away_from(unit, closest_friendly_unit->position);
  else if(closest_enemy_unit != NULL && unit_health >= 0.5f)
    unit_behavior_set_target_position(unit, closest_enemy_unit->position, 120.0f);
  else if(closest_enemy_unit != NULL)
    unit_behavior_evasive_flee_from(unit, closest_enemy_unit->position);
  else
    unit_behavior_movement_stop(unit);

  if(closest_enemy_unit == NULL)
    unit_behavior_head_stop(unit);
  else if(unit_health < 0.2f && vector_distance(unit->position, closest_enemy_unit->position) < 480.0f)
    unit_behavior_overdrive(unit);
  else
    unit_behavior_head_engage_position(unit, closest_enemy_unit->position);
}

static float rand_rangef(float min, float max) {
  return min + ((double)rand() / RAND_MAX) * (max - min);
}

static float rand_rangef_pow2(float min, float max) {
  const float magnitude = (max - min)/2;
  const float result = rand_rangef(-magnitude*magnitude, magnitude*magnitude);
  return sqrtf(result < 0.0f ? -result : result) * (result < 0.0f ? -1.0f : 1.0f);
}

static Projectile * create_unit_projectile(Unit * unit, World * world) {
  Projectile * projectile = &world_entity_allocate(world, PROJECTILE)->projectile;
  projectile_initialize(projectile, unit->position,
    unit->direction + unit->head_direction + rand_rangef(-0.02f, 0.02f), unit->team_id);
  projectile->distance_remaining *= rand_rangef(0.9f, 1.1f);
  return projectile;
}

static void create_unit_projectiles(Unit * unit, World * world) {
  if(unit_is_firing(unit)) {
    while(unit->next_fire_interval < 0) {
      Projectile * projectile = create_unit_projectile(unit, world);
      projectile_update(projectile, -unit->next_fire_interval);
      unit->next_fire_interval += UNIT_FIRE_INTERVAL;
    }
  }
}

static void destroy_unit_touching_projectile(Entity * entity, void * projectile_ptr) {
  Unit * unit = &entity->unit;
  Projectile * projectile = (Projectile*)projectile_ptr;
  if(entity->type == UNIT
  && unit->team_id != projectile->team_id
  && projectile->distance_remaining > 0
  && vector_distance(projectile->position, unit->position) < 12.0f) {
    unit->health -= projectile_damage(projectile);
    projectile->distance_remaining = 0;
  }
}

static void update_projectile_entity(Entity * entity, void * world_ptr) {
  if(entity->type == PROJECTILE) {
    world_iterate_entities((World*)world_ptr, &entity->projectile, destroy_unit_touching_projectile);
  }
}

static void update_unit_entity(Entity * entity, void * world_ptr) {
  if(entity->type == UNIT) {
    World * world = (World*)world_ptr;
    create_unit_projectiles(&entity->unit, world);
    update_unit_behavior(&entity->unit, world);
  }
}

static int rand_rangei(int min, int max) {
  return rand_rangef(min, max);
}

static void setup_unit(Unit * unit, int team_offset, float x, float y) {
  unit_initialize(unit);
  unit->direction = rand_rangef(0, PI2);
  unit->team_id = TEAM_COLOR[team_offset];
  unit->position.x = x + rand_rangef_pow2(-80.0f, 80.0f);
  unit->position.y = y + rand_rangef_pow2(-80.0f, 80.0f);
}

static int event_is_quit_request(SDL_Event * event) {
  return event->type == SDL_QUIT;
}

static void increment_for_unit_entity(Entity * entity, void * count_ptr) {
  int * count = (int*)count_ptr;
  if(entity->type == UNIT)
    (*count)++;
}

static int world_count_units(World * world) {
  int count = 0;
  world_iterate_entities(world, &count, increment_for_unit_entity);
  return count;
}

static CameraMovement camera_movement_from_keyboard_event(SDL_Event * event) {
  CameraMovement camera_movement = (CameraMovement){ (Vector){ 0.0f, 0.0f }, 0.0f };
  SDL_KeyboardEvent key_event = event->key;
  if(!key_event.repeat) {
    switch(key_event.keysym.sym) {
      case SDLK_d:
      case SDLK_RIGHT:
      camera_movement.position.x = 1.0f;
      break;

      case SDLK_a:
      case SDLK_LEFT:
      camera_movement.position.x = -1.0f;
      break;

      case SDLK_w:
      case SDLK_UP:
      camera_movement.position.y = 1.0f;
      break;

      case SDLK_s:
      case SDLK_DOWN:
      camera_movement.position.y = -1.0f;
      break;

      case SDLK_q:
      camera_movement.zoom = -1.0f;
      break;

      case SDLK_e:
      camera_movement.zoom = 1.0f;
      break;
    }

    if(key_event.type == SDL_KEYUP) {
      camera_movement.zoom *= -1.0f;
      vector_multiply_scalar(&camera_movement.position, -1.0f);
    }
  }
  return camera_movement;
}

static int event_is_window_resize(SDL_Event * event, SDL_Window * window) {
  return event->type == SDL_WINDOWEVENT
    && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED
    && event->window.windowID == SDL_GetWindowID(window);
}

static void update_renderer_camera(Renderer * renderer, CameraMovement camera_movement, float delta) {
  vector_multiply_scalar(&camera_movement.position, delta * CAMERA_SPEED / renderer->scale);
  vector_add(&renderer->camera, camera_movement.position);
  renderer->scale *= 1.0f + camera_movement.zoom * CAMERA_ZOOM_SPEED * delta;
}

static void render() {
  Renderer renderer;
  renderer_initialize(&renderer);

  World world;
  world_initialize(&world);

  srand(time(NULL));

  SDL_InitSubSystem(SDL_INIT_TIMER);
  unsigned int start_time = SDL_GetTicks();
  unsigned int last_time = start_time;
  unsigned int last_spawn_time = last_time;

  int is_quit_requested = 0;
  CameraMovement camera_movement = (CameraMovement) { (Vector) { 0.0f, 0.0f }, 0.0f };

  while(!is_quit_requested) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event_is_quit_request(&event))
        is_quit_requested = 1;
      else if(event_is_window_resize(&event, renderer.window))
        renderer_notify_viewport_resized(&renderer);
      else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        CameraMovement event_camera_movement = camera_movement_from_keyboard_event(&event);
        camera_movement.zoom += event_camera_movement.zoom;
        vector_add(&camera_movement.position, event_camera_movement.position);
      }
    }

    unsigned int current_time = SDL_GetTicks();
    int world_unit_count = world_count_units(&world);

    while(UNIT_SPAWN_INTERVAL_MS > 0 && last_spawn_time + UNIT_SPAWN_INTERVAL_MS <= current_time) {
      last_spawn_time += UNIT_SPAWN_INTERVAL_MS;
      int team_offset = rand_rangei(0, TEAM_COUNT);
      float x = rand_rangef_pow2(-640.0f, 640.0f);
      float y = rand_rangef_pow2(-640.0f, 640.0f);
      for(int unit_count = rand_rangei(1, UNIT_SPAWN_MAX_GROUP_SIZE); unit_count >= 0; --unit_count)
        if(world_unit_count++ < UNIT_MAX_SPAWN_COUNT)
          setup_unit(&world_entity_allocate(&world, UNIT)->unit, team_offset, x, y);
    }

    world_iterate_entities(&world, &world, update_projectile_entity);
    world_iterate_entities(&world, &world, update_unit_entity);

    float delta = (current_time - last_time) / 1000.f;

    if(delta > 0) {
      update_renderer_camera(&renderer, camera_movement, delta);
      world_update(&world, delta);
    }

    renderer_clear_color(&renderer, 1.0f, 1.0f, 1.0f);
    renderer_render_world(&renderer, &world);
    renderer_present(&renderer);

    last_time = current_time;
  }

  SDL_QuitSubSystem(SDL_INIT_TIMER);
  world_deinitialize(&world);
  renderer_deinitialize(&renderer);
}

int main(int argc, char **argv) {
  test();
  render();
  return 0;
}
