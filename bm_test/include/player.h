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

//no need de connaitre le type, pour les player on saura qu'on init les spites players
enum Directions {
    BOMBER_D = 0,
    BOMBER_L = 1,
    BOMBER_R = 2,
    BOMBER_U = 3,
};

#endif
