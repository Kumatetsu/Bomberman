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
typedef struct 	s_map_element {
  int	       	destructible; //TEMPORAIRE: Si on fait une t_chain de tous les elem, faut connaitre ceux qui sont destructibles ou pas
  int          	destoyed; //savoir si on doit l'afficher ou non
  int          	x; //x pos  //peut etre pas utile si on save bien le SDL_Rect
  int	       	y; //y pos  //mais peut servir en tant que 1/15 pour connaitre le container et pas avoir a calculer des pixels
  //me voir pour plus d'infos
  SDL_Rect	size; //idee de mat, avoir direct le SDL_Rect a l'init de la struc comme ca plus besoin d'y penser
  enum		type; //pseudo code mais vous voyez l'idee pour savoir quelle struc a generer
}	t_map_element;

#endif
