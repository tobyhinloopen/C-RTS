#include "benchmark.h"

#include <assert.h>

void benchmark_game(Game * game, unsigned int interval_ms, unsigned int duration_ms) {
  int swap_interval = SDL_GL_GetSwapInterval();
  SDL_GL_SetSwapInterval(0);

  for (unsigned int delta = 0; !game->is_quit_requested && delta <= duration_ms; delta += interval_ms)
    game_update_time(game, game->start_time + delta);

  SDL_GL_SetSwapInterval(swap_interval);
}
