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

const int UNIT_INITIAL_SPAWN_COUNT = 0;
const int UNIT_SPAWN_INTERVAL_MS = 2000;
const int UNIT_SPAWN_MAX_GROUP_SIZE = 8;

static void update_unit_behavior(Unit * unit, void * world_ptr) {
  World * world = (World*)world_ptr;
  Unit * closest_enemy_unit;
  Unit * closest_friendly_unit;
  int is_moving_behavior_set = 0;
  if((closest_friendly_unit = unit_behavior_find_closest_friendly_unit(unit, world, 32.0f)) != NULL) {
    Vector move_away_target = closest_friendly_unit->position;
    vector_subtract(&move_away_target, unit->position);
    vector_rotate(&move_away_target, PI);
    vector_add(&move_away_target, unit->position);
    unit_behavior_set_target_position(unit, move_away_target, 0.0f);
    is_moving_behavior_set = 1;
  }
  if((closest_enemy_unit = unit_behavior_find_closest_enemy_unit(unit, world)) != NULL) {
    if(closest_friendly_unit == NULL) {
      if(unit_health_percentage(unit) > 0.5f) {
        unit_behavior_set_target_position(unit, closest_enemy_unit->position, 120.0f);
      } else {
        Vector flee_target = closest_enemy_unit->position;
        vector_subtract(&flee_target, unit->position);
        vector_rotate(&flee_target, HALF_PI);
        vector_add(&flee_target, unit->position);
        unit_behavior_set_target_position(unit, flee_target, 0.0f);
      }
      is_moving_behavior_set = 1;
    }

    if(unit_health_percentage(unit) > 0.2f
    || vector_distance(unit->position, closest_enemy_unit->position) > 480.0f) {
      unit_behavior_look_at(unit, closest_enemy_unit->position);
      float enemy_angle = vector_angle_between(unit->position, closest_enemy_unit->position);
      float angular_diff = remainderf(enemy_angle - unit->direction - unit->head_direction, PI2);
      if(angular_diff < 0)
        angular_diff = - angular_diff;
      if(angular_diff < PI2 * 0.05)
        unit_behavior_open_fire(unit);
      else
        unit_behavior_hold_fire(unit);
    } else {
      unit_behavior_look_forward(unit);
      unit_behavior_hold_fire(unit);
      unit->throttle = 1.3f;
    }
  } else {
    unit_behavior_look_forward(unit);
    unit_behavior_stop(unit);
    unit_behavior_hold_fire(unit);
  }
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

static int event_is_window_resize(SDL_Event * event, SDL_Window * window) {
  return event->type == SDL_WINDOWEVENT
    && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED
    && event->window.windowID == SDL_GetWindowID(window);
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
  while(!is_quit_requested) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event_is_quit_request(&event))
        is_quit_requested = 1;
      else if(event_is_window_resize(&event, renderer.window))
        renderer_notify_viewport_resized(&renderer);
    }

    unsigned int current_time = SDL_GetTicks();

    while(UNIT_SPAWN_INTERVAL_MS > 0 && last_spawn_time + UNIT_SPAWN_INTERVAL_MS <= current_time) {
      last_spawn_time += UNIT_SPAWN_INTERVAL_MS;
      int team_offset = rand_rangei(0, TEAM_COUNT);
      float x = rand_rangef_pow2(-640.0f, 640.0f);
      float y = rand_rangef_pow2(-640.0f, 640.0f);
      for(int unit_count = rand_rangei(1, UNIT_SPAWN_MAX_GROUP_SIZE); unit_count >= 0; --unit_count)
        setup_unit(&world_entity_allocate(&world, UNIT)->unit, team_offset, x, y);
    }

    world_iterate_entities(&world, &world, update_projectile_entity);
    world_iterate_entities(&world, &world, update_unit_entity);

    float delta = (current_time - last_time) / 1000.f;
    if(delta > 0)
      world_update(&world, delta);

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
