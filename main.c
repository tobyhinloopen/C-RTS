#include "test.h"
#include "game.h"

int main(int argc, char **argv) {
  test();

  Game game;
  game_initialize(&game);
  while(!game_is_quit_requested(&game))
    game_update(&game);
  game_deinitialize(&game);

  return 0;
}
