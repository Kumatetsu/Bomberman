#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

#include "client.h"

typedef struct 			s_map_destroyable
{
	int					bomb;
	int					bomb_owner;
	int					start_explode;
	int					wall_destroyable;
}						t_map_destroyable;

typedef struct  		s_game_info
{
	int         		checksum;               /* Un checksum simple */
	int 				tick_time;
	t_player_info		*players[4];
	int 				game_status;
	t_map_destroyable	*map_destroyable[14][15];
} 						t_game_info;

enum MAP_GRID {
	FREE_SLOT=0,
	WALL=1
};

int**					get_array_map();

#endif
