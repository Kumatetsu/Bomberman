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
  int		num_player; //between 0 and 3 for array indexation
  int		x;
  int		y;
  int		current_dir;
  int		bomb_left;
  int		alive;
  int		dying;
  int		connected;
  int		fd;
  SDL_Rect	bomber_sprites[5][4];
  int		index_sprite;
}               t_player_info;

#endif
