/*
** request_handling.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:41:06 2018 hochar_n
** Last update Mon Jul  2 21:03:07 2018 hochar_n
*/

#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"

void	handle_requests(
			t_game_info *game_info,
			t_player_request *player_request
			)
{
  int	**map_pointer;

  map_pointer = get_array_map();
  add_destructible_elements(game_info, map_pointer);
  move_player(game_info, player_request, map_pointer);
  add_bomb_elements(game_info, map_pointer);
  if (player_request->command == PLACE_BOMB)
    place_bomb(game_info, player_request);
}

void	place_bomb(t_game_info *game_info,
		   t_player_request *player_request
		   )
{
  t_player_info	*player;
  int 			i;
  int 			x;
  int 			y;
  t_map_destroyable	*bomb;

  player = NULL;
  for (i = 0; i < 4; i++)
    {
      if (game_info->players[i] == NULL
	  || game_info->players[i]->num_player != player_request->num_player)
	continue;
      player = game_info->players[i];
      if (player->bomb_left == 0)
	return;
    }
  if (player == NULL)
    return;
  bomb = calloc(1, sizeof(t_map_destroyable));
  bomb->bomb = 1;
  bomb->start_explode = game_info->tick_time + 5;
  bomb->bomb_owner = i + 1;
  x = player->x_pos * 8;
  y = player->y_pos * 8;
  game_info->map_destroyable[y][x] =  bomb;
}
