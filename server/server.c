#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl.h"
#include "client.h"

void		init_server(t_sdl *sdl) {
  //launch server thread
  client_loop(sdl);
  //kill thread
  return;
}
