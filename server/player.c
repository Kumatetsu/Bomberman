#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

void add_player(t_server **s, int fd)
{
  t_player *new;
  t_player *tmp;

  if ((new = malloc(sizeof (*new))) == NULL)
    return ;
  new->fd = fd;
  new->identity = NULL;
  new->x = 0;
  new->y = 0;
  new->disabled = 1; //a passer en enum
  new->looking = 0;

  if ((*s)->players == NULL)
    (*s)->players = new;
  else
    {
      tmp = (*s)->players;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }
  printf("player added");
}
