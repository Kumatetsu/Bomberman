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
#include "server.h"
#include "my_put.h"
#include "request.h"
#include "game_info.h"

// for trace
#include "game_info_serialization.h"

void			detail_game_info()
{
  int			i;
  int			j;
  t_game_info		*gi;
  char			details[72];
  char			players_detail[500];
  char			map_detail[23960];
  t_player_info		p;
  t_map_destroyable	m;
  char			total_detail[72 + 500 + 23960];

  gi = get_game_info();
  snprintf(details, sizeof details, "\nchecksum: %d\ntick_time: %d\nnb_client: %d\ngame_status: %d\nid_client: %d", gi->checksum, gi->tick_time, gi->nb_client, gi->game_status, gi->id_client);
  for (i = 0; i < 4; i++)
    {
      p = gi->players[i];
      snprintf(players_detail, sizeof players_detail, "\nPlayers:\nconnected: %d\nalive: %d\ndying: %d\nx_pos: %d\ny_pos: %d\ncurrent_dir: %d\nbomb_left: %d\nfd: %d\nnum_player: %d", p.connected, p.alive, p.dying, p.x_pos, p.y_pos, p.current_dir, p.bomb_left, p.fd, p.num_player);
    }
  for (j = 0; j < 14; j++)
    {
      for (i = 0; i < 15; i++)
	{
	  m = gi->map_destroyable[0][0];
	  if (m.exist == 1)
	    {
	      snprintf(map_detail, sizeof map_detail, "\nMap detail for [%d][%d]:\ny_pos: %d\nx_pos: %d\nbomb: %d\nbomb_owner: %d\nstart_explode:%d\nwall_destroyable: %d\nexist: %d\n", j, i, m.y_pos, m.x_pos, m.bomb, m.bomb_owner, m.start_explode, m.wall_destroyable, m.exist);
	    }

	}
    }
  snprintf(total_detail, sizeof total_detail, "\nGAME INFO:\n%s\nPLAYERS:\n%s\nMAP:\n%s\n", details, players_detail, map_detail);
  printf(total_detail);
  printf("\nopen file\n");
  FILE	*f = fopen("game_info.txt", "w");
  if (f == NULL)
    {
      printf("\nOpen file failed\n");
      return;
    }
  printf("\nfile successfully opened\n");
  //  printf("\nserialized game_info: %s\n", gi);
  fprintf(f, total_detail);

  printf("\nwritten in file done\n");
  fclose(f);
  printf("\nfile closed\n");
}

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
  // add_bomb_elements(game_info, map_pointer);
  // printf("\nbomb element added\n");
  if (player_request->command == PLACE_BOMB)
    {
      printf("\nplace bomb\n");
      /*En standby*/
      // place_bomb(game_info, player_request);
      printf("\nbomb placed\n");
    }
  printf("\nopen file\n");
  detail_game_info();
}

/**
 * Ne correspond pas du tout aux nouvelles structures
**/
// void	place_bomb(t_game_info *game_info,
// 		   t_player_request *player_request
// 		   )
// {
//   t_player_info	player;
//   int 			i;
//   int 			x;
//   int 			y;
//   t_map_destroyable	bomb;

//   printf("\nPLACING BOMB\n");
//   for (i = 0; i < 4; i++)
//     {
//       if (game_info->players[i].connected == 0
// 	  || game_info->players[i].num_player != player_request->num_player)
// 	continue;
//       player = game_info->players[i];
//       if (player.bomb_left == 0)
// 	return;
//     }
//   if (player.connected == 0)
//     return;
//   bomb.exist = 1;
//   player.bomb_left = 0;
//   bomb.bomb = 1;
//   bomb.start_explode = game_info->tick_time + 5;
//   bomb.bomb_owner = i + 1;
//   x = player.x_pos * 8;
//   y = player.y_pos * 8;
//   game_info->map_destroyable[y][x] =  bomb;
// }

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
