#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
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
