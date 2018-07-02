#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

//Ajoute un player à la structure server
void add_player(t_server **s, int fd, int player_rank)
{
  t_player_info *new;

  if ((new = malloc(sizeof (*new))) == NULL)
    return ;

  s = s;
  fd = fd;
  player_rank = player_rank;
  //(*s)->players[player_rank] = new;
  printf("player added");
}
