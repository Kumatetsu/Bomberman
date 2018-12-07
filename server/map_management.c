/*
*
** map_management.c for bomberman in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:37:50 2018
** Last update Sun Jul  1 23:23:51 2018 hochar_n
*/

#include <stdio.h>
#include "sdl.h"
#include "enum.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "game_info.h"
#include "bomb_management.h"
#include "map_management.h"

int		**get_array_map() {
  // TODO: Change 88 and 104 into pixel based values
  static int	map[104][88];
  int 		x;
  int 		y;
  int 		current_x_state;
  int 		current_y_state;

  current_y_state = FREE_SLOT;
  // TODO: Change 88 and 104 into pixel based values
  for (y = 0; y < 88; ++y) {
    current_x_state = WALL;
    if (x % 8 == 0)
      current_y_state = WALL;
    for (x = 0; x < 104; ++x) {
      if (x % 8 == 0 && current_y_state == WALL)
	current_x_state = current_x_state == 1 ? FREE_SLOT : WALL;
      map[x][y] = current_y_state;
    }
  }

  return (int **) map;
}

void			add_destructible_elements(
						  t_game_info *game_info,
						  int **map_pointer
						  )
{
  int 			i;
  int 			j;
  t_map_destroyable	map_destroyable;

  //TODO: check the meaning of 14 and 15 to be sure that works with pixels
  for (i = 1; i < 14; ++i) {
    for (j = 1; j < 15; ++j) {
      printf("\nIn add_destructible_elements with i: %d, j: %d\n", i, j);
      if (game_info->map_destroyable[i][j].exist == 0)
	continue;
      printf("\nadd_destructible_elements: affecting map_destroyable variable\n");
      map_destroyable = game_info->map_destroyable[i][j];
      printf("\nset map_destroyable.exist\n");
      map_destroyable.exist = 1;
      printf("\nset map_pointer with map_destroyable x_pos et y_pos = WALL\n");
      // segfault ici
      map_pointer[map_destroyable.x][map_destroyable.y] = WALL;
      printf("\nIteration done\n");
    }
  }
}


void		        manage_bombs(
				    t_game_info *game_info,
				    int **map_pointer
				    )
{
  int			i;
  int			j;
  t_map_destroyable	map_destroyable;

  printf("\nAdd_bomb_element iterate through map_destroyable\n");
  //TODO: check the meaning of 14 and 15 to be sure that works with pixels
  for (i = 1; i < 14; ++i) {
    for (j = 1; j < 15; ++j) {
      // On vérifie que l'élément peut supporter l'ajout d'une bomb
      printf("\ncheck if map_destroyable %d/%d exist\n", i, j);
      if (game_info->map_destroyable[i][j].exist == 0)
	continue;
      printf("\nset a variable with this gqme_info->map_destroyable\n");
      map_destroyable = game_info->map_destroyable[i][j];
      // si l'emplacement n'est pas une bomb
      // OU une bomb qui n'a pas commencé son explode
      printf("\ncheck map_destroyable content .bomb and .start_explode\n");
      if (map_destroyable.bomb == 0
	  || (map_destroyable.bomb == 1
	      && game_info->tick_time < map_destroyable.start_explode)
	  )
	{
	  printf("\nc'est une bombe, déjà placée, qui n'explose pas\n");
	  continue;
	}
      printf("\ncheck if start_explode + 5 == tick_time (?)\n");
      if (map_destroyable.start_explode + 5 == game_info->tick_time)
	{
	  // c'est une bombe, il est temps qu'elle pète
	  printf("\ncall destroy bomb\n");
	  destroy_bomb(game_info, map_pointer, map_destroyable);
	  continue;
	}
      printf("\ncall trigger_bomb\n");
      // libre, c'est un dépot de bomb, on l'a trigger
      trigger_bomb(game_info, map_pointer, map_destroyable);
      printf("\ntrigger_bomb done\n");
    }
    printf("\nnext column\n");
  }
  printf("\nadd_bomb_elements done\n");
}

int 			is_there_a_wall(
					t_game_info *game_info,
					int** map_pointer,
					int x,
					int y
					)
{
  int			i;
  int			j;
  t_map_destroyable	map_destroyable;

  if (map_pointer[x][y] == WALL)
    return 1;
  //TODO: check the meaning of 14 and 15 to be sure that works with pixels
  for (i = 1; i < 14; ++i) {
    for (j = 1; j < 15; ++j) {
      if (game_info->map_destroyable[i][j].exist == 0
	  || game_info->map_destroyable[i][j].bomb == 1)
	continue;
      map_destroyable = game_info->map_destroyable[i][j];
      if (map_destroyable.y == y && map_destroyable.x == x)
	return 1;
    }
  }
  return 0;
}
