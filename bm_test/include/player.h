#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct  s_player_info
{
    int         connected;
    int         alive;
    int         dying;
    int         x_pos;
    int         y_pos;
    int         current_dir;
    int         bomb_left;
    int         fd;
    int         num_player; //between 0 and 3 because it's easier for my arrays
}               t_player_info;
#endif
