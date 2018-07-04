/*
** game_info.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/common
** 
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
** 
** Started on  Wed Jul  4 09:33:09 2018 MASERA Mathieu
** Last update Wed Jul  4 09:33:11 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include "player.h"
#include "request.h"
#include "sdl.h"
#include "game_info.h"

static t_game_info *game_info;

t_game_info	*get_game_info()
{
  return game_info;
}

void	set_game_info(t_game_info *new_game_info)
{
  game_info = new_game_info;
}
