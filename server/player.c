#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

//Ajoute un player à la structure server
void add_player(t_server **s, int fd, int player_rank)
{
  t_player *new;

  if ((new = malloc(sizeof (*new))) == NULL)
    return ;
  new->fd = fd;
  new->identity = NULL;
  new->x = 0;
  new->y = 0;
  new->disabled = 1; //a passer en enum
  new->looking = 0;

  (*s)->players[player_rank] = new;
  printf("player added");
}
