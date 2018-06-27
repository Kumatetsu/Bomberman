#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"

void	move_player(t_game_info *game_info, t_player_request *player_request)
{
	int	**map_pointer;
	int i;

	map_pointer = get_array_map();
	// player can not go out of the grid, top-left spawn is (x=0,y=0) and bot-right is (x=98,y=82)
	if (player_request->x_pos < 0 || player_request->y_pos < 0 || player_request->x_pos > 98 || player_request->y_pos > 82)
		return;

	// update the static map with the player position
	for (i = 0; i < 4; i++)
	{
		if (game_info->players[i] == NULL)
			continue;
		map_pointer[player_request->x_pos][player_request->y_pos] == 1;
	}
	
	if (map_pointer[player_request->x_pos][player_request->y_pos] == 1)
		return;

	for (i = 0; i < 4; i++)
	{
		if (game_info->players[i] == NULL || game_info->players[i]->num_player != player_request->num_player)
			continue;
		game_info->players[i]->x_pos = player_request->x_pos;
		game_info->players[i]->y_pos = player_request->y_pos;
	}
}