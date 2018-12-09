/*
** moving.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   hochar_n@etna-altenance.net
**
** Started on  Sun Jul  1 17:39:23 2018 hochar_n
** Last update Mon Jul  2 21:01:32 2018 hochar_n
*/

#include <stdio.h>
#include "server.h"
#include "my_put.h"
#include "request.h"
#include "game_info.h"

void	move_player(
		    t_game_info *game_info,
		    t_player_request *player_request,
        int num_player,
		    int **map_pointer
		    )
{
      if (game_info->players[num_player].connected == 0)
	      return;

      // TODO: Check les collisions
      // if (check_collision(map_pointer, player_request) == 0)
      // return;

      switch(player_request->commande) {
        case MOVE_UP:
          game_info->players[num_player].y_pos -= 6;
          break;
        case MOVE_DOWN:
          game_info->players[num_player].y_pos += 6;
          break;
        case MOVE_LEFT:
          game_info->players[num_player].x_pos += 6;
          break;
        case MOVE_DOWN:
          game_info->players[num_player].x_pos -= 6;
          break;
        default:
          return
      }
    }

/*
  TODO: check les collisions
*/
// int	check_collision(
// 			int** map_pointer,
// 			t_player_request *player_request
// 			)
// {
//   int	i;

//   for (i = (player_request->x_pos-3); i < (player_request->x_pos+3); ++i) {
//     if (i < 0)
//       continue;
//     if (map_pointer[player_request->x_pos][player_request->y_pos] == WALL)
//       return 0;
//   }

//   for (i = (player_request->y_pos-3); i < (player_request->y_pos+3); ++i) {
//     if (i < 0)
//       continue;
//     if (map_pointer[player_request->x_pos][player_request->y_pos] == WALL)
//       return 0;
//   }

//   return 1;
// }
