#ifndef _SERVER_REQUEST_H_
#define _SERVER_REQUEST_H_

#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "map.h"

typedef struct s_response_players
{
    enum Response_type id;
    t_player_info players[4];

} t_response_players;

typedef struct s_response_up_pos
{
    enum Response_type id;
    int player_id;
    int x, y;
} t_response_up_pos;

typedef struct s_response_bomb
{
    enum Response_type id;
    t_map_destroyable map_destroyable;
} t_response_bomb;

typedef union u_response_pool {
    enum Response_type id;

    t_response_players response_players;
    t_response_up_pos response_up_pos;
    t_response_bomb response_bomb;
} t_response_pool;
#endif
