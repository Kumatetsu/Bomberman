#include <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "sdl.h"
#include "client.h"
#include "server.h"
#include "thread.h"

//init le thread server et lance un client pour la personne qui host
void		init_server(t_sdl *sdl) {
  t_server	*s;
  pthread_t	t_server;

  s = create_server();
  init_socket(&s);

  if (pthread_create(&t_server, NULL, server_thread, s) == -1)
      return;
  sleep(5);
  sdl->server_welcome = NULL;
  //  client_loop(sdl, s->server_fd);

  return;
}
