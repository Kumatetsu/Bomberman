#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

//Init de la structure serve servant de store des datas.
t_server 	*create_server() {
  t_server	*s;

  s = NULL;
  if ((s = malloc(sizeof (*s))) == NULL)
      return NULL;
  return s;
}
