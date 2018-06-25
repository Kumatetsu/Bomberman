#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct 	s_player_info
{
  int  			connected;
  int	  		alive;
  int   		x_pos;
  int   		y_pos;
  int   		current_dir;
  int   		current_speed;
  int   		max_speed;
  int   		bombs_left;
  int   		bombs_capacity;
  int   		frags;
  int			fd;
} 				t_player_info;

#endif
