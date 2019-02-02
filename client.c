#include "client.h"
#include "assert.h"

void client_initialize(Client * client) {
  vec_init(&client->mods);

  SDL_InitSubSystem(SDL_INIT_TIMER);

  client->delta = 0;
  client->start_time = SDL_GetTicks();
  client->current_time = client->start_time;
  client->last_time = client->start_time;
}

void client_add_module(Client * client, void * data, void (* init)(const Client *, ClientModule *, void *)) {
  ClientModule mod = {
    .data = NULL,
    .name = NULL,
    .init = NULL,
    .tick = NULL,
    .update = NULL,
    .deinit = NULL,
  };
  init(client, &mod, data);
  if (!mod.name) {
    printf("client_add_module: added module doesn't have name");
  }
  if (mod.init) {
    mod.init(client, data);
  }
  vec_push(&client->mods, mod);
}

static int client_tick(Client * client) {
  ClientModule * mod;
  int i;
  int next = 0;
  vec_foreach_ptr(&client->mods, mod, i) {
    if (mod->tick) {
      next = mod->tick(client, mod->data) || next;
    }
  }
  return next;
}

static int client_update_children(Client * client) {
  ClientModule * mod;
  int i;
  int next = 0;
  vec_foreach_ptr(&client->mods, mod, i) {
    if (mod->update) {
      next = mod->update(client, mod->data) || next;
    }
  }
  client->last_time = client->current_time;
  return next;
}

static int client_update_time(Client * client, Uint32 current_time) {
  assert(current_time >= client->current_time);
  client->current_time = current_time;
  client->delta = client->current_time - client->last_time;
  int update_next = client_update_children(client);
  int tick_next = client_tick(client);
  client->last_time = client->current_time;
  return update_next || tick_next;
}

int client_update(Client * client) {
  return client_update_time(client, SDL_GetTicks());
}

void client_deinitialize(Client * client) {
  ClientModule * mod;
  int i;
  vec_foreach_ptr(&client->mods, mod, i) {
    if (mod->deinit) {
      mod->deinit(client, mod->data);
    }
  }
  vec_deinit(&client->mods);
}
