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
#include "static_wall_rect.h"

void		        	manage_bombs(t_game_info *game_info)
{
  int					i;
  t_map_destroyable		map_destroyable;

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

int					bomb_kill_player(int x, int y) {
	t_game_info 	*game_info;
	int				z;
	int				i;
	SDL_Rect 		*walls;

	game_info = get_game_info();
	const SDL_Rect bomb = {x, y, PIXEL_SIZE, PIXEL_SIZE};
	walls = get_walls();

	for (i = 0; i < 82; i++) {
		if (SDL_HasIntersection(&walls[i], &bomb)) {
			printf("\nWALL at %d:%d\n", walls[i].x, walls[i].y);
			printf("bomb explode on WALL\n\n");
			return 1;
		}
	}

	for (i = 0; i < INLINE_MATRIX; ++i) {
		if (!game_info->map_destroyable[i].exist && !game_info->map_destroyable[i].bomb)
			continue;
		const SDL_Rect element = {game_info->map_destroyable[i].x, game_info->map_destroyable[i].y, PIXEL_SIZE, PIXEL_SIZE};
		if (SDL_HasIntersection(&bomb, &element)) {
			game_info->map_destroyable[i].dying = 1;
			game_info->map_destroyable[i].exist = 0;
			printf("bomb explode on wall destroyable\n\n");
			return 1;
		}
	}

	// Loop over players
	for (z = 0; z < (int)(sizeof(game_info->players)/sizeof(game_info->players[0])); ++z) {
		if (&game_info->players[z] != NULL && &game_info->players[z].alive != 0)
		{
			//printf("\nin players stuff\n");
			const SDL_Rect player = {game_info->players[z].x, game_info->players[z].y, PIXEL_SIZE, PIXEL_SIZE};
			if (SDL_HasIntersection(&bomb, &player))
			{
				game_info->players[z].alive = 0;
				game_info->players[z].dying++;
			}
		}
	}

	return 0;
}

void					bomb_check_players(int i) {
	t_game_info 		*game_info;
	t_map_destroyable 	*map_destroyable;
	int					y;
	int					x;
	int					bomb_x;
	int					bomb_y;
	int					is_wall;

	game_info = get_game_info();
	map_destroyable = game_info->map_destroyable;
	bomb_x = map_destroyable[i].x;
	bomb_y = map_destroyable[i].y;

	printf("\nBOMB explode at: %d:%d\n", bomb_x,bomb_y);

//	the kill zone is 3 pixel on the x and 3 on the y.
	for (x = (bomb_x - PIXEL_SIZE); x > (bomb_x - (3 * PIXEL_SIZE)); x -= PIXEL_SIZE) {
		printf("\nBOMB LOOP explode at: %d:%d\n", x, bomb_y);
		is_wall = bomb_kill_player(x, bomb_y);
		if (is_wall) {
			break;
		}
	}

	for (y = (bomb_y - PIXEL_SIZE); y > (bomb_y - (3 * PIXEL_SIZE)); y -= PIXEL_SIZE) {
		printf("\nBOMB LOOP explode at: %d:%d\n", bomb_x, y);
		is_wall = bomb_kill_player(bomb_x, y);
		if (is_wall) {
			break;
		}
	}

	for (x = (bomb_x + PIXEL_SIZE); x < (bomb_x + (3 * PIXEL_SIZE)); x += PIXEL_SIZE) {
		printf("\nBOMB LOOP explode at: %d:%d\n", x, bomb_y);
		is_wall = bomb_kill_player(x, bomb_y);
		if (is_wall) {
			break;
		}
	}

	for (y = (bomb_y + PIXEL_SIZE); y < (bomb_y + (3 * PIXEL_SIZE)); y += PIXEL_SIZE) {
		printf("\nBOMB LOOP explode at: %d:%d\n", bomb_x, y);
		is_wall = bomb_kill_player(bomb_x, y);
		if (is_wall) {
			break;
		}
	}
}

int	is_wall(t_game_info *game_info, int x, int y)
{
  int	i;

  i = x + (y * COLUMNS);
  if (game_info->map_destroyable[i].wall_destroyable == 1)
    return 1;
  return 0;
}
