#include "test.h"
#include "game.h"

#include "mod/event.h"
#include "mod/render.h"

int main(int argc, char **argv) {
  test();

  Game game;
  game_initialize(&game, 2);

  game_add_module(&game, mod_event);
  game_add_module(&game, mod_render);

  while(!game.is_quit_requested)
    game_update(&game);

  game_deinitialize(&game);

  return 0;
}
