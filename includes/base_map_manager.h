
/*
** base_map.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:24 2018 hochar_n
** Last update Thu Jul  5 21:38:25 2018 hochar_n
*/

#ifndef _BASE_MAP_MANAGER_H_
#define _BASE_MAP_MANAGER_H_

SDL_Rect init_rect(int x, int y, int w, int z);
t_map init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type);
void *draw_all(void *arg);
void *rebuild_map(void *arg);
int get_element_type(int i, int j);

#endif /* !_BASE_MAP_MANAGER_H_ */
