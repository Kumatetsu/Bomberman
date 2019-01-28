#include <stdio.h>
#include <unistd.h>
#include "sdl.h"
#include "player_info.h"
#include "server_request.h"

void notify_actual_players(t_player_info players[4]) {
    t_response_players players_pool;
    int i;

    players_pool.id = PLAYERS;
    for (i = 0; i < 4; i++)
        printf("connected: %d\n\n\n", players[i].connected);
        players_pool.players[i] = players[i];

    for (i = 0; i < 4; i++)
        if (0 == players[i].fd)
            return;
        write(players[i].fd, &players_pool, sizeof(players_pool));
}
