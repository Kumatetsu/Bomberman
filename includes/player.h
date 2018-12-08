/*
** player.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:37:54 2018 hochar_n
** Last update Thu Jul  5 21:37:56 2018 hochar_n
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

/*
 DEPRECATED PART
*/
#include <SDL2/SDL.h>

typedef struct	s_player
{
  int		fd;
  char  *identity;
  int		x;
  int		y;
  int		disabled;
  int		looking;
  int		index_sprite;
  SDL_Rect	bomber_sprites[5][4];
}		t_player;

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
/*
  END OF DEPRECATED PART
 */
int add_player(t_srv **srv, int fd);
int accept_players(t_srv **srv);
#endif
