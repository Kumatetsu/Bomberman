/*
** player.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
** 
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
** 
** Started on  Wed Jul  4 09:37:49 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:50 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

//Ajoute un player à la structure server
void add_player(t_server **s, int fd, int player_rank)
{
  t_player *new_player;

  if ((new_player = malloc(sizeof (*new_player))) == NULL)
    return ;

  s = s;
  fd = fd;
  player_rank = player_rank;
  //(*s)->players[player_rank] = new;
  printf("player added");
}
