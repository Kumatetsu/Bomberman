#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

#include "client.h"

typedef struct  	s_game_info
{
	int         	checksum;               /* Un checksum simple */
	int 			tick_time;
	t_player_infos	*players[4];
	int 			game_status;
} 					t_game_info;

#endif
