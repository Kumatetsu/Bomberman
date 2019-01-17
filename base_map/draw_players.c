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
#include "bomber_sprites.h"
#include "client_request.h"
#include "server.h"
#include "game_info.h"
#include "draw_players.h"


int		draw_players(void *arg, t_game_info *client_game_info)
{
  int		i;
  t_player_info player;

  if (client_game_info != NULL)
    {
      for (i = 0; i < 4; i++)
	{
	  player = client_game_info->players[i];
	  if (player.connected && player.alive)
	    {
	      if (!draw_player(arg, player))
		return (0);
	    }
	}
    }
  else
    {
      printf("\nclient_game_info is null and must not...\n");
      return (0);
    }
  return (1);
}

/*
 * return 1 if success 0 if failure
 */
int		draw_player(void *arg, t_player_info player_info)
{
  int		error;
  t_data	*data = (t_data*)arg;
  SDL_Rect	sprite_container;

  sprite_container = getBomberSprites(player_info.num_player, player_info.direction_sprite, player_info.action_sprite);
  if (player_info.dying > 0)
    sprite_container = getBomberSprites(player_info.num_player, die, 3 - player_info.dying);
  SDL_Rect	dest_rect = {player_info.x, player_info.y, PIXEL_SIZE, 24 * 3};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &sprite_container,
			 &dest_rect);

  if (error < 0)
    {
      SDL_ShowSimpleMessageBox(0, "drawing Player Failed",
			     SDL_GetError(), data->window);
      return (0);
    }
  return (1);
}
