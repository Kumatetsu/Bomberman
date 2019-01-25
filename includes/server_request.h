#ifndef _SERVER_REQUEST_H_
#define _SERVER_REQUEST_H_

typedef struct s_response_players
{
    int           id;
    t_player_info players[4];

} t_response_player;

typedef struct s_response_up_pos
{
    int id;
    int x, y;
} t_response_up_pos;

typedef struct s_response_bomb
{
    int               id;
    t_map_destroyable map_destroyable;
} t_response_bomb;

typedef union u_response_pool {
    int id;

    t_response_player response_players;
    t_response_up_pos response_up_pos;
    t_response_bomb   response_bomb;
} t_response_pool;
#endif
