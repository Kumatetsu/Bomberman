#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sdl.h"
//#include "server.h"

//typedef struct	s_player {
  //int	fd;
  //char	*identity;
  //int	x;
  //int	y;
  //int	disabled;
  //int	looking;
  //}	t_player;
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
  int	index_sprite;
  SDL_Rect bomber_sprites[5][4];
}               t_player_info;

//no need de connaitre le type, pour les player on saura qu'on init les spites players
enum BomberSpriteDir {bomber_d = 0,
		      bomber_l = 1,
		      bomber_r = 2,
		      bomber_u = 3,
		      die = 4,
		      not_move = 0,
		      move_r = 1,
		      transit_move = 2,
		      move_l = 3};

void *move_player_down(void *arg);
void *move_player_up(void *arg);
void *move_player_right(void *arg);
void *move_player_left(void *arg);
void *move_player_stop(void *arg);

#endif
