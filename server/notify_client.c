#include <stdio.h>
#include <unistd.h>
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "server_request.h"
#include "moving.h"

void notify_actual_players(t_srv **server, int id_player)
{
    printf("sever: in notify actual players\n");
    t_response_players players_pool;

    players_pool.id = PLAYERS;
    for (id_player = 0; id_player < 4; id_player++)
        players_pool.players[id_player] = (*server)->players[id_player];

    for (id_player = 0; id_player < 4; id_player++)
    {
        if (-1 == (*server)->players[id_player].fd)
            continue;
        write((*server)->players[id_player].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_up(t_srv **server, int id_player)
{
    t_response_up_pos players_pool;
    int i;
    printf("in move up player\n");
    move_player(server, MOVE_UP, id_player);

    players_pool.id = MOVE_U;
    players_pool.player_id = id_player;
    players_pool.x = (*server)->players[id_player].x;
    players_pool.y = (*server)->players[id_player].y;
    players_pool.direction = (*server)->players[id_player].direction_sprite;
    players_pool.action = (*server)->players[id_player].action_sprite;
    for (i = 0; i < 4; i++)
    {
        if (-1 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_down(t_srv **server, int id_player)
{
    t_response_up_pos players_pool;
    int i;
    printf("in move down player\n");
    move_player(server, MOVE_DOWN, id_player);

    players_pool.id = MOVE_D;
    players_pool.player_id = id_player;
    players_pool.x = (*server)->players[id_player].x;
    players_pool.y = (*server)->players[id_player].y;
    players_pool.direction = (*server)->players[id_player].direction_sprite;
    players_pool.action = (*server)->players[id_player].action_sprite;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_left(t_srv **server, int id_player)
{
    t_response_up_pos players_pool;
    int i;
    printf("in move left player\n");
    move_player(server, MOVE_LEFT, id_player);

    players_pool.id = MOVE_L;
    players_pool.player_id = id_player;
    players_pool.x = (*server)->players[id_player].x;
    players_pool.y = (*server)->players[id_player].y;
    players_pool.direction = (*server)->players[id_player].direction_sprite;
    players_pool.action = (*server)->players[id_player].action_sprite;
    for (i = 0; i < 4; i++)
    {
        if (-1 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_right(t_srv **server, int id_player)
{
    t_response_up_pos players_pool;
    int i;
    printf("in move right player\n");
    move_player(server, MOVE_RIGHT, id_player);

    players_pool.id = MOVE_R;
    players_pool.player_id = id_player;
    players_pool.x = (*server)->players[id_player].x;
    players_pool.y = (*server)->players[id_player].y;
    players_pool.direction = (*server)->players[id_player].direction_sprite;
    players_pool.action = (*server)->players[id_player].action_sprite;
    for (i = 0; i < 4; i++)
    {
        if (-1 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_put_bomb(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;
    printf("server put_bomb for player: %d\n", id_player);
    players_pool.id = BOMB;
    for (i = 0; i < 4; i++)
    {
        if (-1 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}
