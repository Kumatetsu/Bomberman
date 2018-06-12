#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "sdl.h"
#include "client.h"
#include "server.h"
#include "thread.h"

//Thread du server permettant de faire tourner le server
void 			*server_thread(void *s_info) {
  t_server 		*s;
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  int			i;

  s = (t_server *)(s_info);
  // a passer dans une fonction add thread_sockets ?
  memset(&client_sin, 0, sizeof(struct sockaddr_in));
  client_sin_len = sizeof(client_sin);
  for (i = 0; i < 4; i ++) {
    printf("waiting connection\n");
    cs = accept(s->server_fd, (struct sockaddr *)&client_sin, &client_sin_len);
    if (cs == -1)
      pthread_exit(NULL);
    printf("one connected\n");
    add_player(&s, cs, i);
  }
  pthread_exit(NULL);
}
