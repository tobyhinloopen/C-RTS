#ifndef GAME_MODULE_H
#define GAME_MODULE_H

#include "game.h"

typedef struct {
  void (* initialize)(Game * game);
  void (* tick)(Game * game);
  void (* update)(Game * game, unsigned int delta_since_tick);
  void (* deinitialize)(Game * game);
} GameModule;

#endif
