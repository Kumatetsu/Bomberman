/*
** game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Tue Jun 26 17:36:48 2018 BILLAUD Jean
*/

#include <stdlib.h>
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
