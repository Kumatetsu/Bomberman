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
    printf("client: update pos\n");
    printf("client: moving id: %d\n", response_pool->response_up_pos.player_id);
    printf("client from: x:%d y:%d to x:%d y:%d", (*game_info)->players[response_pool->response_up_pos.player_id].x, (*game_info)->players[response_pool->response_up_pos.player_id].y, response_pool->response_up_pos.x, response_pool->response_up_pos.y);
    (*game_info)->players[response_pool->response_up_pos.player_id].x = response_pool->response_up_pos.x;
    (*game_info)->players[response_pool->response_up_pos.player_id].y = response_pool->response_up_pos.y;
    (*game_info)->players[response_pool->response_up_pos.player_id].direction_sprite = response_pool->response_up_pos.direction;
    (*game_info)->players[response_pool->response_up_pos.player_id].action_sprite = response_pool->response_up_pos.action;
    printf("client: end update pos\n");
}

void update_bomb(t_game_info **game_info, t_response_pool *response_pool)
{
    (*game_info)->map_destroyable[response_pool->response_bomb.index] = response_pool->response_bomb.bomb;
    return;
}

void update_players(t_game_info **game_info, t_response_pool *response_pool)
{
    int i;
    printf("client: update players\n");
    for (i = 0; i < 4; i++)
    {
        (*game_info)->players[i] = response_pool->response_players.players[i];
    }
    printf("client: end update players\n");
}

void update_explosion(t_game_info **game_info, t_response_pool *response_pool)
{
    int i;

    for (i = 0; i < 13; i++)
    {
        printf("client receive index %d\n", response_pool->bomb_explosion.index[i]);
        (*game_info)->map_destroyable[response_pool->bomb_explosion.index[i]] = response_pool->bomb_explosion.explosion[i];
    }

    for (i = 0; i < INLINE_MATRIX; i++)
    {
        if ((*game_info)->map_destroyable[i].exist == 1)
            printf("exist in all? %d index %d\n", (*game_info)->map_destroyable[i].exist, i);
    }
    for (i = 0; i < 4; i++)
    {
        (*game_info)->players[i] = response_pool->bomb_explosion.players[i];
    }
}
