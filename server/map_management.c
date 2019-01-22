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
#include "constant.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "game_info.h"
// #include "bomb_management.h"
#include "base_map_manager.h"

void		        manage_bombs(t_game_info *game_info)
{
  int			i;
  t_map_destroyable	map_destroyable;

  printf("\nAdd_bomb_element iterate through map_destroyable\n");
  for (i = 1; i < INLINE_MATRIX; ++i) {
    // On vérifie que l'élément peut supporter l'ajout d'une bomb
    printf("\ncheck if map_destroyable %d exist\n", i);
    if (game_info->map_destroyable[i].exist == 0)
      continue;
    printf("\nset a variable with this gqme_info->map_destroyable\n");
    map_destroyable = game_info->map_destroyable[i];
    printf("\nif its a bomb\n");
    if (map_destroyable.bomb == 1)
      {
	printf("\ncheck if start_explode == tick_time (?)\n");
    	if (map_destroyable.start_explode == game_info->tick_time)
	  {
	    // c'est une bombe, il est temps qu'elle pète
	    printf("\ncall destroy bomb\n");
	    //	    destroy_bomb(game_info, map_destroyable);
	    continue;
	  }
	printf("\ncall trigger_bomb\n");
	//	trigger_bomb(game_info, map_pointer, map_destroyable);
	printf("\ntrigger_bomb done\n");
      }
  }
  printf("\nmanage_bomb done\n");
}

int	is_wall(t_game_info *game_info, int x, int y)
{
  int	i;

  i = x + (y * COLUMNS);
  if (game_info->map_destroyable[i].wall_destroyable == 1)
    return 1;
  return 0;
}
