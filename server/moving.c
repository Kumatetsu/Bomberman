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
		    int num_player
		    )
{
  int	i;

  printf("\nmoveplayer, check if player is in map\n");
  if (player_request->x_pos < 0 || player_request->y_pos < 0
      || player_request->x_pos > 720 || player_request->y_pos > 624)
    return;

  printf("\nmoveplayer check_collision call\n");
  if (check_collision(map_pointer, player_request) == 0)
    return;

  printf("\nWill iterate throught players\n");
  for (i = 0; i < 4; i++)
    {
      printf("\nselect player in game_info corresponding to player request\n");
      if (game_info->players[i].connected == 0
	  || game_info->players[i].num_player != player_request->num_player)
	continue;

      printf("\nset x_pos in gameinfo->player from player request x_pos (?)\n");
      game_info->players[i].x_pos = player_request->x_pos;
      printf("\nset y_pos in gameinfo->player from player request y_pos\n");
      game_info->players[i].y_pos = player_request->y_pos;
      printf("\ngo to next iteration\n");
    }
  printf("\niteration done\n");
}

int	check_collision(
			int** map_pointer,
			t_player_request *player_request
			)
{
  int	i;

  printf("\ncheck_collision first iteration throught players\n");
  for (i = (player_request->x_pos-3); i < (player_request->x_pos+3); ++i) {
    printf("\nif i < 0\n");
    if (i < 0)
      continue;

    printf("\nchek_collision check if WALL to map_pointer[playerrequestX][playerrequestY], if true: return\n");
    // segfault ici
    if (map_pointer[player_request->x_pos][player_request->y_pos] == WALL)
      {
	printf("\nis Wall, return\n");
	return 0;
      }
  }
  printf("\nsecond iteration of check_collision\n");
  for (i = (player_request->y_pos-3); i < (player_request->y_pos+3); ++i) {
    printf("\nif i < 0\n");
    if (i < 0)
      continue;
    printf("\nchek_collision check if WALL to map_pointer[playerrequestX][playerrequestY], if true: return\n");
    if (map_pointer[player_request->x_pos][player_request->y_pos] == WALL)
      {
	printf("\nis Wall, return\n");
	return 0;
      }
  }
  printf("\nBoth iterations done, check_collision done\n");
  return 1;
}
