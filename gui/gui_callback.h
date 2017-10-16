#ifndef GUI_CALLBACK_H
#define GUI_CALLBACK_H

typedef struct {
  void (* func)(void * arg);
  void * arg;
} GUICallback;

#endif
