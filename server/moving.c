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
#include "my_put.h"
#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "game_info.h"
#include "moving.h"
#include "map_management.h"

void	move_player(
		    t_game_info *game_info,
		    t_player_request *player_request,
		    int num_player
		    )
{
  num_player = player_request->num_player;

  printf("\nmoveplayer, check if player is in map\n");
  // Commenté sinon on empêche le déplacement.
  // if (player_request->x < 0 || player_request->y < 0
  //     || player_request->x > 104 || player_request->y > 88)
  //   return;

  /*
  * Pour le moment on check pas les collisions on veut juste bouger
  */
  // printf("\nmoveplayer check_collision call\n");
  // if (check_collision(map_pointer, player_request) == 0)
  //   return;


  int new_x, new_y;
  // x = width, y = height, sprite = visual to apply in the front
  int new_x, new_y, sprite_index;

  printf("\ncheck if player is connected\n");
  if (game_info->players[num_player].connected == 0)
	  return;

  printf("\nmoveplayer, check if player is in map\n");
  if (player_request->x < 0 || player_request->y < 0
      || player_request->x > 104 || player_request->y > 88)
    return;

  switch (player_request->command)
  {
    case MOVE_UP:
      new_y = game_info->players[num_player].y - 6;
      sprite_index = bomber_u;
      // printf("\nPLAYER MOVED UP, command:%d, y_pos: %d", player_request->command, game_info->players[num_player].y_pos);
      break;

    case MOVE_DOWN:
      new_y = game_info->players[num_player].y + 6;
      sprite_index = bomber_d;
      // printf("\nPLAYER MOVED DOWN, command:%d, y_pos: %d", player_request->command, game_info->players[num_player].y_pos);
      break;

    case MOVE_RIGHT:
      new_x = game_info->players[num_player].x + 6;
      sprite_index = bomber_r;
      // printf("\nPLAYER MOVED DOWN, command:%d, x_pos: %d", player_request->command, game_info->players[num_player].x_pos);
      break;

    case MOVE_LEFT:
      new_x = game_info->players[num_player].x - 6;
      sprite_index = bomber_l;
      // printf("\nPLAYER MOVED DOWN, command:%d, x_pos: %d", player_request->command, game_info->players[num_player].x_pos);
      break;

    default:
      break;
  }

  /*
  * Pour le moment on check pas les collisions on veut juste bouger
  */
  printf("\nmoveplayer check_collision call\n");
  if (check_collision(game_info, new_x, new_y, num_player) == 0)
     return;

  game_info->players[num_player].x = new_x;
  game_info->players[num_player].y = new_y;
  game_info->players[num_player].index_sprite = sprite_index;

  set_game_info(game_info);
}

 int	check_collision(
      t_game_info *game_info,
 			int requested_x,
      int requested_y,
      int num_player
 			)
 {
   int            y,x;
  //  int            **map_pointer;
   const SDL_Rect player = {requested_x, requested_y, 16 * 3, 24 * 3};

   printf("\ncheck_collision first iteration throught players\n");

    //  map_pointer = get_array_map();
     // Loop over map_pointer
    //  for (y = 1; y <= (int)(sizeof(map_pointer)/sizeof(map_pointer[0])); ++y) {
    //     for (x = 1; x <= (int)(sizeof(map_pointer[y])/sizeof(map_pointer[y][0])); ++x) {
    //         printf("\n%d : %d\n", x, y);
    //       if (map_pointer[x][y] == WALL)
    //       {
    //         const SDL_Rect element = {x, y, 16 * 3, 24 * 3};
    //         if (SDL_HasIntersection(&player, &element))
    //           return 0;
    //       }
    //     }
    //   }

     // Loop over map_desctructible
     for (y = 0; y < (int)(sizeof(game_info->map_destroyable)/sizeof(game_info->map_destroyable[0])); ++y) {
        for (x = 0; x < (int)(sizeof(game_info->map_destroyable[y])/sizeof(game_info->map_destroyable[y][0])); ++x) {
          if (game_info->map_destroyable[x][y].exist || game_info->map_destroyable[x][y].bomb)
          {
            printf("\nin destructible stuff\n");
            const SDL_Rect element = {x, y, 16 * 3, 24 * 3};
            if (SDL_HasIntersection(&player, &element))
              return 0;
          }
        }
      }

     // Loop over players
     for (y = 0; y < (int)(sizeof(game_info->players)/sizeof(game_info->players[0])); ++y) {
        if (game_info->players->num_player != num_player && &game_info->players[y] != NULL)
        {
          printf("\nin players stuff\n");
          const SDL_Rect other_player = {game_info->players[y].x, game_info->players[y].y, 16 * 3, 24 * 3};
          if (SDL_HasIntersection(&player, &other_player))
            return 0;
        }
      }

   printf("\nBoth iterations done, check_collision done\n");
   return 1;
 }
