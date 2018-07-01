#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "socket.h"
#include "server.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"

t_game_info *create_game_info(int fd1, int fd2, int fd3, int fd4) {
    t_game_info *game_info;
    t_map_destroyable *map_destroyable;
    int i;

    game_info = calloc(1, sizeof(t_game_info));
    for (i = 0; i < 3; ++i) {
        game_info->players[i] = calloc(1, sizeof(t_player_info));
        game_info->players[i]->connected = 1;
        game_info->players[i]->bomb_left = 1;
        game_info->players[i]->num_player = i + 1;
        switch (i) {
            case 0:
                game_info->players[i]->fd = fd1;
                game_info->players[i]->x_pos = 2;
                game_info->players[i]->y_pos = 2;
                game_info->players[i]->current_dir = BOMBER_L;
                break;
            case 1:
                game_info->players[i]->fd = fd2;
                game_info->players[i]->x_pos = 101;
                game_info->players[i]->y_pos = 2;
                game_info->players[i]->current_dir = BOMBER_D;
                break;
            case 2:
                game_info->players[i]->fd = fd3;
                game_info->players[i]->x_pos = 2;
                game_info->players[i]->y_pos = 85;
                game_info->players[i]->current_dir = BOMBER_U;
                break;
            case 3:
                game_info->players[i]->fd = fd4;
                game_info->players[i]->x_pos = 101;
                game_info->players[i]->y_pos = 85;
                game_info->players[i]->current_dir = BOMBER_R;
                break;
        }
    }
    for (i=0; i < 32; ++i)
    {
        map_destroyable = calloc(1, sizeof(t_map_destroyable));
        map_destroyable->wall_destroyable = 1;
        map_destroyable->y_pos = random_at_most(11);
        map_destroyable->x_pos = random_at_most(13);
        game_info->map_destroyable[map_destroyable->y_pos][map_destroyable->x_pos] = map_destroyable;
    }

    return game_info;
}

long random_at_most(long max) {
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
            num_bins = (unsigned long) max + 1,
            num_rand = (unsigned long) RAND_MAX + 1,
            bin_size = num_rand / num_bins,
            defect   = num_rand % num_bins;

    long x;
    do {
        x = random();
    }
        // This is carefully written not to overflow
    while (num_rand - defect <= (unsigned long)x);

    // Truncated division is intentional
    return x/bin_size;
}
