#include <stdio.h>
#include "sdl.h"
#include "enum.h"
#include "constant.h"
#include "map.h"
#include "server.h"
#include "player_info.h"
#include "game_info.h"
#include "server_request.h"

void update_pos(t_game_info **game_info, t_response_pool *response_pool)
{
    (*game_info)->players[response_pool->response_up_pos.player_id].x = response_pool->response_up_pos.x;
    (*game_info)->players[response_pool->response_up_pos.player_id].y = response_pool->response_up_pos.y;
    (*game_info)->players[response_pool->response_up_pos.player_id].direction_sprite = response_pool->response_up_pos.direction;
    (*game_info)->players[response_pool->response_up_pos.player_id].action_sprite = response_pool->response_up_pos.action;
}

void update_bomb(t_game_info **game_info, t_response_pool *response_pool)
{
    (*game_info)->map_destroyable[response_pool->response_bomb.index] = response_pool->response_bomb.bomb;
    return;
}

void update_players(t_game_info **game_info, t_response_pool *response_pool)
{
    int i;
    printf("client in update players\n");
    for (i = 0; i < 4; i++)
    {
        printf("client player id:%d, alive:%d", response_pool->response_players.players[i].num_player, response_pool->response_players.players[i].alive);
        (*game_info)->players[i] = response_pool->response_players.players[i];
    }
}

void update_explosion(t_game_info **game_info, t_response_pool *response_pool)
{
    int i;

    if (response_pool->id == EXPLOSION)
    {
        for (i = 0; i < 13; i++)
            (*game_info)->map_destroyable[response_pool->bomb_explosion.index[i]] = response_pool->bomb_explosion.explosion[i];
        for (i = 0; i < 4; i++)
        {
            if (!response_pool->bomb_explosion.players[i].alive)
                (*game_info)->players[i] = response_pool->bomb_explosion.players[i];
        }
    }
    else
        for (i = 0; i < 13; i++)
            (*game_info)->map_destroyable[response_pool->end_explosion.index[i]] = response_pool->end_explosion.explosion[i];
}
