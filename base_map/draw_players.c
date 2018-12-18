/*
** draw_players.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/base_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:30:48 2018 MASERA Mathieu
** Last update Wed Jul  4 09:30:50 2018 MASERA Mathieu
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "constant.h"
#include "enum.h"
#include "player_info.h"
#include "map.h"
#include "data.h"
#include "draw_players.h"
#include "bomber_sprites.h"


void *draw_player(void *arg, t_player_info player_info)
{
  int     error;
  t_data	*data = (t_data*)arg;
  SDL_Rect sprite_container;

  sprite_container = getBomberSprites(player_info.num_player, bomber_d, not_move);
  SDL_Rect	dest_rect = {player_info.x, player_info.y, 16 * 3, 24 * 3};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &sprite_container,
			 &dest_rect);

  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player1 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}
