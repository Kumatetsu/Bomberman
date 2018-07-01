/*
** request_handling.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:41:06 2018 hochar_n
** Last update Sun Jul  1 18:06:21 2018 hochar_n
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
	int	i;

	map_pointer = get_array_map();
	add_destructible_elements(game_info, map_pointer);

	add_bomb_elements(game_info, map_pointer);
}
