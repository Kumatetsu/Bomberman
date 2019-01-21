/*
** request_handling.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:41:06 2018 hochar_n
** Last update Mon Jul  2 21:03:07 2018 hochar_n
*/

#include <stdio.h>
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "my_put.h"
#include "map.h"
#include "game_info.h"
#include "moving.h"
#include "coord_index_swapper.h"
#include "collision.h"
#include "base_map_manager.h"
#include "request_handling.h"

// dev
#include "detail_game_info.h"

void	detail_player(t_player_info p)
{
  printf("\nPlayer:");
  printf("\nnum_player: %d", p.num_player);
  printf("\nx: %d", p.x);
  printf("\ny: %d", p.y);
  printf("\ncurrent_dir: %d", p.current_dir);
  printf("\nbomb_left:%d", p.bomb_left);
  printf("\nalive: %d", p.alive);
  printf("\ndying: %d", p.dying);
  printf("\nconnected: %d", p.connected);
  printf("\nsocket number: %d", p.fd);
}

// le map_pointer segfault
void	handle_requests(t_game_info *game_info,	t_player_request *player_request)
{
  int	num_player;

  num_player = player_request->num_player;
  // detail_player(game_info->players[player_request->num_player]);
  // Les commandes de mouvement étant assimilées à un int plus grand
  // On a juste à check si la commande est supérieur aà PLACE_BOMB
  if (game_info->players[num_player].alive && game_info->players[num_player].dying == 0)
    {
      if (player_request->command > PLACE_BOMB )
	{
	  move_player(game_info, player_request, num_player);
	}
      if (player_request->command == PLACE_BOMB)
	{
	  place_bomb(game_info, player_request);
	}
    }
  else if (game_info->players[num_player].dying > 0)
    {
      game_info->players[num_player].dying--;
    }
}

/**
 * @params (*)t_game_info
 * @params (*)t_player_request
 * @return 1 -> success 0 -> fail
**/
int			place_bomb(t_game_info *game_info, t_player_request *player_request)
{
  t_player_info		player;
  int 			index;
  t_map_destroyable	bomb;

  printf("\nPLACING BOMB\n");
  player = game_info->players[player_request->num_player];
  if (player.connected == 0)
    return (0);
  bomb.exist = 1;
  player.bomb_left--;
  bomb.bomb = 1;
  bomb.start_explode = game_info->tick_time + TICK_IN_SEC * 2; // TICK_IN_SEC == 1000 / SLEEP
  bomb.bomb_owner = player_request->num_player;
  // cohabitation principe de cases et principe pixels

  switch (player.direction_sprite)
  {
    case bomber_d:
      // on place en dessous des pieds
      bomb.x = player.x;
      bomb.y = player.y + PIXEL_SIZE + 21;
      break;

    case bomber_l:
      bomb.x = player.x - PIXEL_SIZE;
      // différence de taille entre le SDL_Rect des bombers et celui des bombes (7px * 3)
      bomb.y = player.y + 21;
      break;

    case bomber_r:
      bomb.x = player.x + PIXEL_SIZE;
      // différence de taille entre le SDL_Rect des bombers et celui des bombes (7px * 3)
      bomb.y = player.y + 21;
      break;

    case bomber_u:
      bomb.x = player.x;
      bomb.y = player.y - PIXEL_SIZE;
      break;

    default:
      break;
  }

  index = coord_to_index(bomb.x, bomb.y);
  int new_x = index_to_x(index);
  int new_y = index_to_y(index);
  bomb.x = new_x;
  bomb.y = new_y;
  /*
  const SDL_Rect zone = init_rect(bomb.x + 20, bomb.y + 20, 2, 2);
  if (has_collision_with_wall(zone))
    {
      printf("\nBOMB HAS COLLISION\n");
      return 0;
    }
  */
  if (game_info->map_destroyable[index].exist)
    {
      printf("\nYou can't place a bomb here, already one in that case\n");
      return (0);
    }
  else
    {
      printf("\nPlacing bomb at index: %d, position: %d/%d\n", index, bomb.x, bomb.y);
      game_info->map_destroyable[index] = bomb;
      return (1);
    }
}

void	add_request_to_server(t_srv **srv, t_player_request *player_request)
{
 int i;

 for (i = 0; i < 8; ++i)
   {
     if ((*srv)->requests[i] != NULL)
         continue;

     (*srv)->requests[i] = player_request;
   }
}
