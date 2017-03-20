#include "test.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mod/event.h"
#include "mod/projectile_unit_impact.h"
#include "mod/random_spawn.h"
#include "mod/render.h"

int main(int argc, char **argv) {
  srand(time(NULL));

  printf("Entity: %lu; EntityPool: %lu\n", sizeof(Entity), sizeof(EntityPool));

  test();

  Game game;
  game_initialize(&game, 4);

  game_add_module(&game, mod_event);
  game_add_module(&game, mod_projectile_unit_impact);
  game_add_module(&game, mod_random_spawn);
  game_add_module(&game, mod_render);

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);

  return 0;
}
