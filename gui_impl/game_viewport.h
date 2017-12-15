#ifndef GUI_IMPL_GAME_VIEWPORT
#define GUI_IMPL_GAME_VIEWPORT

#include "../game.h"
#include "../gui/gui_viewport.h"
#include "../vector.h"

typedef struct {
  Game * game;
  GUIViewport * viewport;
} GameViewport;

void game_viewport_initialize(GameViewport *, Game *, GUIViewport *);

#endif
