#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct	s_player {
  int	fd;
  char	*identity;
  int	x;
  int	y;
  int	disabled;
  int	looking;
}	t_player;

//no need de connaitre le type, pour les player on saura qu'on init les spites players

#endif
