/*
** map.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:42 2018 hochar_n
** Last update Thu Jul  5 21:38:43 2018 hochar_n
*/

#ifndef _MAP_H_
#define _MAP_H_

typedef struct	s_map_destroyable
{
  int		x;
  int		y;
  int		bomb_owner;
  int		dying;
  int		start_explode;
  int		bomb;
  int		fire;
  int		wall_destroyable;
  int		exist;
}		t_map_destroyable;

typedef struct	s_map
{
  SDL_Rect	src_rect;
  SDL_Rect	dest_rect;
  texture_type	texture_type;
}		t_map;

#endif /* !_MAP_H_ */
