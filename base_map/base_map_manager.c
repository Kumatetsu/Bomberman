/*
** base_map_manager.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/base_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:30:34 2018 MASERA Mathieu
** Last update Wed Jul  4 09:30:35 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "bomber_sprites.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "player.h"
#include "map.h"
#include "data.h"
#include "draw_base_map.h"
#include "draw_players.h"
#include "game_info.h"
#include "game_map.h"
#include "base_map_manager.h"

// wrapper to init an SDL_Rect
SDL_Rect	pixel_rect(int x, int y)
{
  SDL_Rect	tmp = {x, y, PIXEL_SIZE, PIXEL_SIZE};

  return (tmp);
}

SDL_Rect	init_rect(int x, int y, int w, int z)
{
  SDL_Rect	temp = {x, y, w, z};

  return (temp);
}

t_map	init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type)
{
  t_map map;

  map.src_rect = src;
  map.dest_rect = dest;
  map.texture_type = type;
  return (map);
}

void		*draw_all(void *arg)
{
  int		i;
  t_game_info	*game_info;
  
  game_info = get_game_info();
  draw_map_model(arg);
  draw_pannel(arg);
  draw_timer(arg);
  if (game_info != NULL)
    {
      for (i = 0; i < 4; i++)
	{
	  if (game_info->players[i].connected && game_info->players[i].alive)
	    draw_player(arg, game_info->players[i]);
	}
    }
  return (NULL);
}

void		*rebuild_map(void *arg) {
  t_data	*data = (t_data*)arg;
  int		i, j;

  for (i = 0; i < 14; i++)
    {
      for (j = 0; j < 15; j++)
	{
	  if (data->renderer != NULL)
	    {
	      SDL_RenderCopy(data->renderer, data->texture,
			     &(data->array_map[i][j].src_rect),
			     &(data->array_map[i][j].dest_rect));
	    }
	}
    }
  return (NULL);
}

void		build_destroyables(void *arg)
{
  int		i, error;
  t_data	*data = (t_data*)arg;

  error = 0;
  for (i = 0; i < INLINE_MATRIX; i++)
    {
      if (data->map_destroyable[i].exist)
	{
	  error = SDL_RenderCopy(data->renderer, data->texture,
				 &(data->destroyable_drawer[i].src_rect),
				 &(data->destroyable_drawer[i].dest_rect));
	  printf("\nDestroyable place at %d:%d, texture: %d\n", data->map_destroyable[i].x, data->map_destroyable[i].y, data->destroyable_drawer[i].texture_type);
	}
    }
  if (error > 0)
    SDL_ShowSimpleMessageBox(0, "drawing destroyable failed", SDL_GetError(), data->window);
}

int get_element_type(int i, int j) {
    int code;

    if (j == J_BEGIN || j == J_BEGIN + 12 || i == I_BEGIN || i == I_BEGIN + 14) {
        code = WALL;
    } else if (j == J_BEGIN + 1 || (j % 2 != J_BEGIN % 2 && i % 2 == I_BEGIN % 2)) {
        code = FREE_SLOT;
    } else if (i % 2 != I_BEGIN % 2) {
        code = FREE_SLOT;
    } else if (i % 2 == I_BEGIN % 2) {
        code = WALL;
    } else {
        code = 500;
    }
    return code;
}
