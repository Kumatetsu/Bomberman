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
#include "time_tick.h"
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
void	handle_requests(
			t_game_info *game_info,
			int num_player,
			t_player_request *player_request
			)
{
  // int	**map_pointer;

  detail_game_info();
  // printf("\nget_array_map\n");
  // map_pointer = get_array_map();
  printf("\nmap_pointer ok\n");
  // Cette fonction segfault
  //  add_destructible_elements(game_info, map_pointer);
  printf("\ndestructible element added\n");
  // Les commandes de mouvement étant assimilées à un int plus grand
  // On a juste à check si la commande est supérieur aà PLACE_BOMB
  if (player_request->command > PLACE_BOMB )
    move_player(game_info, player_request, num_player);
  printf("\nplayer moved\n");
  // dans server/map_management.c
  // manage_bombs(game_info, map_pointer);
  // printf("\nbomb element managed\n");
  if (player_request->command == PLACE_BOMB)
    {
      printf("\nplace bomb\n");
      // dans ce fichier
      place_bomb(game_info, player_request);
      printf("\nbomb placed\n");
    }
  printf("\nopen file\n");
  detail_game_info();
}

/**
 * Ne correspond pas du tout aux nouvelles structures
**/
void			place_bomb(t_game_info *game_info, t_player_request *player_request)
{
  t_player_info		player;
  int 			x;
  int 			y;
  t_map_destroyable	item;

  printf("\nPLACING BOMB\n");
  // retrieve player
  player = game_info->players[player_request->num_player];
  // pour poser une bombe, le joueur doit être
  // connecté, vivant, non mourrant et avoir des bombes
  printf("\ntest if player can put a bomb\n");
  if (player.connected == 0
      || player.alive == 0
      || player.dying
      || player.bomb_left == 0)
    return;
  // on rempli l'item destroyable
  printf("\nset item\n");
  item.exist = 1;
  item.bomb = 1;
  // la bombe explosera dans environ 5 secondes (constant based)
  item.start_explode = game_info->tick_time + sec_in_tick() * 5;
  item.bomb_owner = player.num_player;
  // place là où est le joueur, besoin de déterminer la direction
  printf("\nset x and y: %d and %d\n", player.x, player.y);
  x = player.x;
  y = player.y;
  printf("\nset map destroyable to %d:%d\n", x, y);
  game_info->map_destroyable[y][x] = item;
  printf("\nmap destroyable setted\n");
  player.bomb_left--;
}

void	add_request_to_server(t_srv **srv, t_player_request *player_request)
{
 int	i;

 for (i = 0; i < 8; ++i)
   {
     if ((*srv)->requests[i] != NULL)
         continue;

     (*srv)->requests[i] = player_request;
   }
}
