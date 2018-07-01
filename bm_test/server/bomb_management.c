/*
** bomb_management.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Sun Jul  1 22:10:22 2018 hochar_n
*/

#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"

void			trigger_bomb(
				     t_game_info *game_info,
				     int **map_pointer,
				     t_map_destroyable *bomb
				     )
{
  int			k;
  int			i;
  int			j;
  int			is_blocked;
  int 			x;
  int 			y;
  int 			current_pos;
  int 			pos;
  t_map_destroyable	*presence;

  is_blocked = 0;
  for (j=0; j<2; ++j)
    {
      pos = (i == 0 ? bomb->x_pos : bomb->y_pos);
      for (i = pos; i < pos + 8; ++i)
	{
	  current_pos = i == 0 ? bomb->y_pos : bomb->x_pos;
	  for (k = (current_pos-3); k < (current_pos+3); ++k) {
	    if (k == 0 || is_blocked == 1)
	      {
		is_blocked = (k == 0 ? 0 : 1);
		continue;
	      }
	    x = i == 0 ? k : pos;
	    y = i == 0 ? pos : k;
	    if (map_pointer[x][y] == WALL)
	      is_blocked = 1; continue;
	    map_pointer[x][y] = FIRE;
	    presence = get_element_at_pos(game_info, x, y);
	    if (presence != NULL && presence->bomb == 0)
	      presence->dying++; is_blocked =1;
	    else if (presence != NULL && presence->bomb == 1
		     && bomb->start_explode > game_info->tick_time)
	      {
		bomb->start_explode = game_info->tick_time;
		trigger_bomb(game_info, map_pointer, presence);
		is_blocked = 1;
	      }
	  }
	}
    }
}

void			destroy_bomb(
				     t_game_info *game_info,
				     int **map_pointer,
				     t_map_destroyable *bomb_to_destroy
				     )
{
  int			i;
  int			j;
  int			k;
  int 			is_blocked;
  t_map_destroyable	*map_destroyable;

  is_blocked = 0;
  for (k = (bomb_to_destroy->y_pos-3); k < (bomb_to_destroy->y_pos+3); ++k) {
    if (k == 0 || is_blocked == 1)
      {
	is_blocked = (k == 0 ? 0 : 1);
	continue;
      }
    if (map_pointer[bomb_to_destroy->x_pos][k] == WALL)
      {
	is_blocked = 1;
	continue;
      }
    for (i = 1; i < 14; ++i) {
      for (j = 1; j < 15; ++j) {
	if (game_info->map_destroyable[i][j] == NULL
	    || game_info->map_destroyable[i][j]->bomb == 1)
	  continue;
	is_blocked = 1;
	map_destroyable = game_info->map_destroyable[i][j];
	free(map_destroyable);
	game_info->map_destroyable[i][j] = NULL;
      }
    }
  }
  is_blocked = 0;
  for (k = (bomb_to_destroy->x_pos-3); k < (bomb_to_destroy->x_pos+3); ++k) {
    if (k == 0 || is_blocked == 1)
      {
	is_blocked = (k == 0 ? 0 : 1);
	continue;
      }
    if (map_pointer[k][bomb_to_destroy->y_pos] == WALL)
      {
	is_blocked = 1;
	continue;
      }
    for (i = 1; i < 14; ++i) {
      for (j = 1; j < 15; ++j) {
	if (game_info->map_destroyable[i][j] == NULL
	    || game_info->map_destroyable[i][j]->bomb == 1)
	  continue;
	map_destroyable = game_info->map_destroyable[i][j];
	free(map_destroyable);
	game_info->map_destroyable[i][j] = NULL;
      }
    }
  }
  for (i = 0; i < 4; ++i) {
    if (game_info->players[i] == NULL)
      continue;
    game_info->players[i]->bomb_left = 1;
  }
  free(bomb_to_destroy);
  game_info->map_destroyable[i][j] = NULL;
}

t_map_destroyable	*get_element_at_pos(t_game_info *game_info, int x, int y)
{
  int			i;
  int			j;
  t_map_destroyable	*map_destroyable;

  for (i = 1; i < 14; ++i) {
    for (j = 1; j < 15; ++j) {
      if (game_info->map_destroyable[i][j] == NULL
	  || game_info->map_destroyable[i][j]->bomb == 1)
          continue;
      map_destroyable = game_info->map_destroyable[i][j];
      if (map_destroyable->y_pos == y && map_destroyable->x_pos == x)
          return map_destroyable;
    }
  }
  return NULL;
}
