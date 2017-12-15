#include "game_viewport.h"
#include <assert.h>
#include "../renderer.h"

static void render_entity(Entity * entity, void * viewport_ptr) {
  const GUIViewport * viewport = (GUIViewport *)viewport_ptr;

  switch(entity->type) {
    case UNIT:
      if(gui_viewport_contains_world_position(viewport, entity->unit.position, HALF_UNIT_TEXTURE_SIZE))
        renderer_render_unit(&entity->unit);
      break;
    case PROJECTILE:
      if(gui_viewport_contains_world_position(viewport, entity->projectile.position, PROJECTILE_LENGTH))
        renderer_render_projectile(&entity->projectile);
      break;
    case FACTORY:
      if(gui_viewport_contains_world_position(viewport, entity->factory.position, HALF_FACTORY_TEXTURE_SIZE))
        renderer_render_factory(&entity->factory);
      break;
    case NONE: break;
  }
}

static void viewport_renderer_callback(GUIViewport * viewport, void * game_ptr) {
  Game * game = (Game*)game_ptr;
  world_iterate_entities(&game->world, viewport, render_entity);
}

void game_viewport_initialize(GameViewport * game_viewport, Game * game, GUIViewport * viewport) {
  assert(!viewport->render_func);
  assert(!viewport->render_arg);
  game_viewport->game = game;
  game_viewport->viewport = viewport;
  viewport->render_func = viewport_renderer_callback;
  viewport->render_arg = game;
}
