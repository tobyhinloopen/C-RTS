#ifndef CLIENT_H
#define CLIENT_H

#include <time.h>
#include "vendor/vec.h"
#include <SDL2/SDL.h>

typedef struct Client Client;

typedef struct {
  void * data;
  const char * name;
  void (* init)(const Client *, void * data);
  int (* tick)(const Client *, void * data);
  int (* update)(const Client *, void * data);
  void (* deinit)(const Client *, void * data);
} ClientModule;

struct Client {
  vec_t(ClientModule) mods;
  Uint32 start_time;
  Uint32 current_time;
  Uint32 delta;
  Uint32 last_time;
};

void client_initialize(Client *);
void client_add_module(Client *, void *, void (* init)(const Client *, ClientModule * mod, void *));
int client_update(Client *);
void client_deinitialize(Client *);

#endif
