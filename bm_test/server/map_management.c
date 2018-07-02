#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"

int					**get_array_map() {
	static int 		map[104][88];
	int 			x;
	int 			y;
	int 			current_x_state;
	int 			current_y_state;

	current_y_state = FREE_SLOT;
	for (y = 0; y < 88; ++y) {
		current_x_state = WALL;
		if (x % 8 == 0)
			current_y_state = WALL;
		for (x = 0; x < 104; ++x) {
			if (x % 8 == 0 && current_y_state == WALL)
				current_x_state = current_x_state == 1 ? FREE_SLOT : WALL;
			map[x][y] = current_y_state;
		}
	}

	return (int **) map;
}

void					add_destructible_elements(t_game_info *game_info, int** map_pointer)
{
	int 				i;
	int 				j;
	t_map_destroyable	*map_destroyable;

	for (i = 1; i < 14; ++i) {
		for (j = 1; j < 15; ++j) {
			if (game_info->map_destroyable[i][j] == NULL)
				continue;
			map_destroyable = game_info->map_destroyable[i][j];
			map_pointer[map_destroyable->x_pos][map_destroyable->y_pos] = WALL;
		}
	}
}

void					add_bomb_elements(t_game_info *game_info, int** map_pointer)
{
	int 				i;
	int 				j;
	t_map_destroyable	*map_destroyable;

	for (i = 1; i < 14; ++i) {
		for (j = 1; j < 15; ++j) {
			if (game_info->map_destroyable[i][j] == NULL)
				continue;
			map_destroyable = game_info->map_destroyable[i][j];
			if (map_destroyable->bomb == 0
				|| (map_destroyable->bomb == 1 && game_info->tick_time < map_destroyable->start_explode))
				continue;
			//TODO: we will need to adjust the +2 to the nb of tick to reach 2 seconds 30
			if (map_destroyable->start_explode+2 == game_info->tick_time)
			{
				destroy_bomb(game_info, map_pointer, map_destroyable);
				continue;
			}
			trigger_bomb(game_info, map_pointer, map_destroyable);
		}
	}
}

int 					is_there_a_wall(t_game_info *game_info, int** map_pointer, int x, int y)
{
	int 				i;
	int 				j;
	t_map_destroyable	*map_destroyable;

	if (map_pointer[x][y] == WALL)
		return 1;
	for (i = 1; i < 14; ++i) {
		for (j = 1; j < 15; ++j) {
			if (game_info->map_destroyable[i][j] == NULL || game_info->map_destroyable[i][j]->bomb == 1)
				continue;
			map_destroyable = game_info->map_destroyable[i][j];
			if (map_destroyable->y_pos == y && map_destroyable->x_pos == x)
				return 1;
		}
	}

	return 0;
}