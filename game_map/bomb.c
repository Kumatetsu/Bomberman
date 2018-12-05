/*
** bomb.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/game_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:35:44 2018 MASERA Mathieu
** Last update Wed Jul  4 09:35:45 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "request.h"
#include "player.h"
#include "sdl.h"
#include "base_map.h"

void *bomb_sprite(void *arg)
{
  t_data *data = (t_data*)arg;
  data->destroyable[bomb][bomb_s] = init_rect(17, 255, 16, 17);
  data->destroyable[bomb][bomb_m] = init_rect(33, 255, 16, 17);
  data->destroyable[bomb][bomb_l] = init_rect(50, 38, 16, 17);
  return NULL;
}
