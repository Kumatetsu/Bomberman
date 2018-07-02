#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"

// This will be place in the server loop after merge!!!
void	handle_requests(t_game_info *game_info, t_player_request *player_request)
{
	int	**map_pointer;
	int	i;

	map_pointer = get_array_map(); // get the map base
	add_destructible_elements(game_info, map_pointer); // add all the destructible elements on the map

//	Call moving player for each request

//	for (i = 0; i < 4; i++)
//	{
//		if (game_info->players[i] == NULL || game_info->players[i]->num_player != player_request->num_player)
//			continue;
//
//	}

//	Add bombs explosions and stuff
	add_bomb_elements(game_info, map_pointer);
}
