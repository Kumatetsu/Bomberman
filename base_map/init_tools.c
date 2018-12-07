/*
** init_tools.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/base_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:31:00 2018 MASERA Mathieu
** Last update Wed Jul  4 09:31:01 2018 MASERA Mathieu
*/

#include "system.h"
#include "player.h"
#include "sdl.h"
#include "request.h"
#include "base_map.h"

SDL_Rect init_rect(int x, int y, int w, int z) {
  SDL_Rect temp = {x, y, w, z};
  return (temp);
}

t_map init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type)
{
  t_map map;
  map.src_rect = src;
  map.dest_rect = dest;
  map.texture_type = type;
  return (map);
}
