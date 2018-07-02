/*
** player.h for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/include
** 
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
** 
** Started on  Mon Jul  2 21:08:53 2018 hochar_n
** Last update Mon Jul  2 21:08:54 2018 hochar_n
*/

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

enum Directions {
    BOMBER_D = 0,
    BOMBER_L = 1,
    BOMBER_R = 2,
    BOMBER_U = 3,
};

#endif /* !_PLAYER_H_ */
