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
#include "server.h"
#include "request.h"
#include "game_info.h"
#include "base_map.h"

int **get_array_map()
{
    static int map[14][15];
    int height, width, i, j, type;

    height = 1;
    for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
        width = 0;
        // largeur
        for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
            type = draw_map_loop(i, j);
            if (type == FREE_SLOT_SHADOW)
                type = FREE_SLOT;

            map[height][width] = type;
            width++;
        }
        height++;
    }

    return (int **) map;
}

void add_destructible_elements(
    t_game_info *game_info,
    int **map_pointer
)
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

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
      map_pointer[map_destroyable.x_pos][map_destroyable.y_pos] = WALL;
      printf("\nIteration done\n");
    }
}


// détermine si l'on peut placer une bombe,
// si une bombe est à l'emplacement, détermine si 
void			add_bomb_elements(
					  t_game_info *game_info,
					  int **map_pointer
					  )
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

  printf("\nAdd_bomb_element iterate through map_destroyable\n");
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

// code mort
int is_there_a_wall(
    t_game_info *game_info,
    int **map_pointer,
    int x,
    int y
)
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

    if (map_pointer[x][y] == WALL)
        return 1;
    for (i = 1; i < 14; ++i) {
        for (j = 1; j < 15; ++j) {
            if (game_info->map_destroyable[i][j].exist == 0
                || game_info->map_destroyable[i][j].bomb == 1)
                continue;
            map_destroyable = game_info->map_destroyable[i][j];
            if (map_destroyable.y_pos == y && map_destroyable.x_pos == x)
                return 1;
        }
    }

    return 0;
}
