/*
** bomb_management.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Mon Jul  2 20:58:04 2018 hochar_n
*/

#include <stdio.h>
#include "sdl.h"
#include "enum.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "game_info.h"
#include "bomb_management.h"

// utilité de wrapper la boucle?
void			trigger_bomb(
				     t_game_info *game_info,
				     t_map_destroyable bomb
				     )
{
  int			i;
  int			j;
  int 			pos;

  for (j=0; j<2; ++j)
    {
      pos = (i == 0 ? bomb.x : bomb.y);
      for (i = pos; i < pos + 8; ++i)
	{
	  apply_bomb_to_position(bomb, game_info, i);
	}
    }
}

// logique pas comprise
void			apply_bomb_to_position(
					       t_map_destroyable bomb,
					       t_game_info *game_info,
					       int i
					       )
{
  int 			k;
  int 			is_blocked;
  int 			x;
  int 			y;
  int 			current_pos;
  int 			pos;
  t_map_destroyable	presence;

  pos = (i == 0 ? bomb.x : bomb.y);
  is_blocked = 0;
  current_pos = i == 0 ? bomb.y : bomb.x;
  for (k = (current_pos-3); k < (current_pos+3); ++k) {
    if (k == 0 || is_blocked == 1)
      {
	is_blocked = (k == 0 ? 0 : 1);
	continue;
      }
    // ??????
    // x = -3 < current_pos < +3
    // OU x = i == 0 ? x : y
    x = i == 0 ? k : pos;
    y = i == 0 ? pos : k;
    if (map_pointer[x][y] == WALL)
      {
	is_blocked = 1;
	continue;
      }
    map_pointer[x][y] = FIRE;
    presence = get_element_at_pos(game_info, x, y);
    apply_explosion(presence, bomb, game_info, map_pointer);
  }
}

void			destroy_bomb(
				     t_game_info *game_info,
				     int **map_pointer,
				     t_map_destroyable bomb_to_destroy
				     )
{
  int			i;
  int			j;
  int			k;
  int 			is_blocked;

  is_blocked = 0;
  for (k = (bomb_to_destroy.y-3); k < (bomb_to_destroy.y+3); ++k) {
    if (k == 0 || is_blocked == 1)
      {
	is_blocked = (k == 0 ? 0 : 1);
	continue;
      }
    if (map_pointer[bomb_to_destroy.x][k] == WALL)
      {
	is_blocked = 1;
	continue;
      }
    for (i = 1; i < 14; ++i) {
      for (j = 1; j < 15; ++j) {
	if (game_info->map_destroyable[i][j].exist == 0
	    || game_info->map_destroyable[i][j].bomb == 1)
	  continue;
	is_blocked = 1;
	game_info->map_destroyable[i][j].exist = 0;
      }
    }
  }
  is_blocked = 0;
  for (k = (bomb_to_destroy.x-3); k < (bomb_to_destroy.x+3); ++k) {
    if (k == 0 || is_blocked == 1)
      {
	is_blocked = (k == 0 ? 0 : 1);
	continue;
      }
    if (map_pointer[k][bomb_to_destroy.y] == WALL)
      {
	is_blocked = 1;
	continue;
      }
    for (i = 1; i < 14; ++i) {
      for (j = 1; j < 15; ++j) {
	if (game_info->map_destroyable[i][j].exist == 0
	    || game_info->map_destroyable[i][j].bomb == 1)
	  continue;
	game_info->map_destroyable[i][j].exist = 0;
      }
    }
  }
  for (i = 0; i < 4; ++i) {
    if (game_info->players[i].connected == 0 && bomb_to_destroy.bomb_owner == i + 1)
      continue;
    game_info->players[i].bomb_left = 1;
  }
  bomb_to_destroy.exist = 0;
}

t_map_destroyable	get_element_at_pos(t_game_info *game_info, int x, int y)
{
  int			i;
  int			j;
  t_map_destroyable	map_destroyable;

  for (i = 1; i < 14; ++i) {
    for (j = 1; j < 15; ++j) {
      if (game_info->map_destroyable[i][j].exist == 0
	  || game_info->map_destroyable[i][j].bomb == 1)
	continue;
      map_destroyable = game_info->map_destroyable[i][j];
      if (map_destroyable.y == y && map_destroyable.x == x)
	return map_destroyable;
    }
  }
  return map_destroyable;
}

int apply_explosion(
		    t_map_destroyable presence,
		    t_map_destroyable bomb,
		    t_game_info *game_info,
		    int **map_pointer
		    )
{
  if (presence.exist == 1 && presence.bomb == 0)
    presence.dying++;
  else if (presence.exist == 1 && presence.bomb == 1
	   && bomb.start_explode > game_info->tick_time)
    {
      bomb.start_explode = game_info->tick_time;
      trigger_bomb(game_info, map_pointer, presence);
    }
  else
    return 0;
  return 1;
}
