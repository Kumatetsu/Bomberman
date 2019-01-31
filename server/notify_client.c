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
    t_response_players players_pool;
    int i;

    players_pool.id = PLAYERS;
    for (i = 0; i < 4; i++)
        printf("connected: %d\n\n\n", (*server)->players[i].connected);
    players_pool.players[i] = (*server)->players[i];

    write((*server)->players[id_player].fd, &players_pool, sizeof(players_pool));
}

void notify_move_up(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;

    move_player(server, MOVE_UP, id_player);

    players_pool.id = MOVE;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_down(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;

    move_player(server, MOVE_DOWN, id_player);

    players_pool.id = MOVE;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_left(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;

    move_player(server, MOVE_LEFT, id_player);

    players_pool.id = MOVE;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_move_right(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;

    move_player(server, MOVE_RIGHT, id_player);

    players_pool.id = MOVE;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}

void notify_put_bomb(t_srv **server, int id_player)
{
    t_response_players players_pool;
    int i;

    move_player(server, MOVE_UP, id_player);

    players_pool.id = BOMB;
    for (i = 0; i < 4; i++)
    {
        if (0 == (*server)->players[i].fd)
            continue;
        write((*server)->players[i].fd, &players_pool, sizeof(players_pool));
    }
}
