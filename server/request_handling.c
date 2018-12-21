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
#include "request_handling.h"

// dev
#include "detail_game_info.h"

// le map_pointer segfault
void	handle_requests(t_game_info *game_info,	t_player_request *player_request)
{
  // int	**map_pointer;
  int	num_player;

  num_player = player_request->num_player;
  //  detail_game_info();
  // Les commandes de mouvement étant assimilées à un int plus grand
  // On a juste à check si la commande est supérieur aà PLACE_BOMB
  if (player_request->command > PLACE_BOMB )
    {
      move_player(game_info, player_request, num_player);
      printf("\nplayer moved\n");
    }
  // dans server/map_management.c
  // manage_bombs(game_info, map_pointer);
  // printf("\nbomb element managed\n");
  if (player_request->command == PLACE_BOMB)
    {
      printf("\nplace bomb\n");
      place_bomb(game_info, player_request);
      printf("\nbomb placed\n");
    }
  // detail_game_info();
}

/**
 * Ne correspond pas du tout aux nouvelles structures
**/
void			place_bomb(t_game_info *game_info, t_player_request *player_request)
{
  t_player_info		player;
  int 			index;
  t_map_destroyable	bomb;

  printf("\nPLACING BOMB\n");
  player = game_info->players[player_request->num_player];
  if (player.connected == 0)
    return;
  bomb.exist = 1;
  player.bomb_left--;
  bomb.bomb = 1;
  bomb.start_explode = game_info->tick_time + TICK_IN_SEC; // time_in_tick pour faire 5 secondes en tick?
  bomb.bomb_owner = player_request->num_player;
  // cohabitation principe de cases et principe pixels ahahahah
  bomb.x = player.x;
  bomb.y = player.y;
  index = (bomb.x + bomb.y * COLUMNS) / PIXEL_SIZE;
  printf("\nPlacing bomb at index: %d, position: %d/%d\n", index, bomb.x, bomb.y);
  game_info->map_destroyable[index] = bomb;
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
