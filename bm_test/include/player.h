#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct 	s_player_infos
{
  char  		connected;
  char  		alive;
  int   		x_pos;
  int   		y_pos;
  int   		current_dir;
  int   		current_speed;
  int   		max_speed;
  int   		bombs_left;
  int   		bombs_capacity;
  int   		frags;
} 				t_player_infos;

#endif
