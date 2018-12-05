/*
** player_info.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:40:02 2018 hochar_n
** Last update Thu Jul  5 21:40:03 2018 hochar_n
*/

#ifndef _PLAYER_INFO_H_
#define _PLAYER_INFO_H_

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

enum Directions {
    BOMBER_D = 0,
    BOMBER_L = 1,
    BOMBER_R = 2,
    BOMBER_U = 3,
};

#endif
