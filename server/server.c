#include <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "client.h"
#include "server.h"

void		init_server(t_sdl *sdl) {
  t_server	*s;
  pid_t		pid;

  s = create_server();
  init_socket(&s);


  return;
}
