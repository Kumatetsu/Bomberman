#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include "server.h"

typedef struct	s_player {
  int	fd;
  char	*identity;
  int	x;
  int	y;
  int	disabled;
  int	looking;
  SDL_Rect bomber_sprites[5][3];
}	t_player;

//no need de connaitre le type, pour les player on saura qu'on init les spites players
enum BomberSpriteDir {bomber_d = 0,
		      bomber_l = 1,
		      bomber_r = 2,
		      bomber_u = 3,
		      not_move = 0,
		      die = 4};

void *move_player(void *arg);

#endif
