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
#include "constant.h"

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

  // x = width, y = height, sprite = visual to apply in the front
  int new_x, new_y, sprite_direction;

  printf("\ncheck if player is connected\n");
  if (game_info->players[num_player].connected == 0)
	  return;

  printf("\nmoveplayer, check if player is in map\n");
  if (player_request->x < 0 || player_request->y < 0
      || player_request->x > 15 * PIXEL_SIZE || player_request->y > 13 * PIXEL_SIZE)
    return;

  switch (player_request->command)
  {
    case MOVE_UP:
      new_y = game_info->players[num_player].y - 6;
      new_x = game_info->players[num_player].x;
      sprite_direction = bomber_u;
      printf("\nPLAYER MOVED UP, command:%d, y_pos: %d", player_request->command, new_y);
      break;

    case MOVE_DOWN:
      new_y = game_info->players[num_player].y + 6;
      new_x = game_info->players[num_player].x;
      sprite_direction = bomber_d;
      printf("\nPLAYER MOVED DOWN, command:%d, y_pos: %d", player_request->command, new_y);
      break;

    case MOVE_RIGHT:
      new_x = game_info->players[num_player].x + 6;
      new_y = game_info->players[num_player].y;
      sprite_direction = bomber_r;
      printf("\nPLAYER MOVED DOWN, command:%d, x_pos: %d", player_request->command, new_x);
      break;

    case MOVE_LEFT:
      new_x = game_info->players[num_player].x - 6;
      new_y = game_info->players[num_player].y;
      sprite_direction = bomber_l;
      printf("\nPLAYER MOVED DOWN, command:%d, x_pos: %d", player_request->command, new_x);
      break;

    default:
      player_request->command = not_move;
      break;
  }

  /*
  * Pour le moment on check pas les collisions on veut juste bouger
  */
  printf("\nmoveplayer check_collision call\n");
  if (check_collision(game_info, new_x, new_y, num_player) == 0)
     return;

  if (game_info->players[num_player].alive)
  {
    game_info->players[num_player].x = new_x;
    game_info->players[num_player].y = new_y;
  }

  change_sprite(&game_info->players[num_player], sprite_direction, player_request->command);

  set_game_info(game_info);
}

void change_sprite(t_player_info *player, int sprite_direction, int player_command)
{
  int next_action_sprite, next_direction_sprite;

  // Death management
  if (player->alive == 0)
  {
    next_direction_sprite = die;
    switch (player->action_sprite)
    {
      case 0:
        next_action_sprite = 1;
        break;
      case 1:
        next_action_sprite = 2;
        break;
      case 2:
        break;
      default:
        next_action_sprite = 0;
        break;
    }
    player->direction_sprite = next_direction_sprite;
    player->action_sprite = next_action_sprite;
    return;
  }

  // Well there are no many ways to don't move...
  if (player_command == not_move)
  {
    next_action_sprite = not_move;
    player->action_sprite = next_action_sprite;
    return;
  }

  // Here we manage the fluidity of the move
  if (player->direction_sprite == sprite_direction)
  {
    switch (player->action_sprite)
    {
      case move_l:
        next_action_sprite = move_r;
        break;

      case move_r:
        next_action_sprite = move_l;

      default:
        break;
    }

    player->action_sprite = next_action_sprite;
    return;
  }

  // It's like a turn arround, so we only change the direction (by using the direction calculated before), not the action
  player->direction_sprite = sprite_direction;
}

 int	check_collision(
      t_game_info *game_info,
 			int requested_x,
      int requested_y,
      int num_player
 			)
 {
   int            y, i;
  //  int  y_player_block, x_player_block;
  //  int            max_x, max_y, min_x, min_y;
  //  int            **map_pointer;

  // We need to abstract the shadow and the head of the player of the collision process, that mean to take only the 42x42 pixels of the player
  // To do that we remove a pixel on the left and 6 on the top so we have the foots and the center of the player! (The player initialy is 42x48)
   const SDL_Rect player = {requested_x - 1, requested_y - 6, PIXEL_SIZE - 6, PIXEL_SIZE - 6};

  //  y_player_block = (int) (requested_y / PIXEL_SIZE);
  //  x_player_block = (int) (requested_x / PIXEL_SIZE);

  //  max_y = y_player_block + 3;
  //  // min_y should always be greater than 1 because 0 is not playable
  //  min_y = (y_player_block - 3) > 1 ? y_player_block - 3 : 1;

  //  max_x = x_player_block + 3;
  //  min_x = (x_player_block - 3) > 0 ? x_player_block - 3 : 0;

   printf("\ncheck_collision first iteration throught players\n");

    //  map_pointer = get_array_map();
     // Loop over map_pointer
    //  for (y = 1; y <= (int)(sizeof(map_pointer)/sizeof(map_pointer[0])); ++y) {
    //     for (x = 1; x <= (int)(sizeof(map_pointer[y])/sizeof(map_pointer[y][0])); ++x) {
    //         printf("\n%d : %d\n", x, y);
    //       if (map_pointer[x][y] == WALL)
    //       {
    //         const SDL_Rect element = {x, y, PIXEL_SIZE, PIXEL_SIZE};
    //         if (SDL_HasIntersection(&player, &element))
    //           return 0;
    //       }
    //     }
    //   }

    // // Loop over map_desctructible
    // for (y = min_y; y < max_y; ++y)
    // {
    //    for (x = min_x; x < max_x; ++x)
    //    {
    //      if (game_info->map_destroyable[x][y].exist || game_info->map_destroyable[x][y].bomb)
    //      {
    //        //printf("\nin destructible stuff\n");
    //        const SDL_Rect element = {game_info->map_destroyable[x][y].x, game_info->map_destroyable[x][y].y, PIXEL_SIZE, PIXEL_SIZE};
    //        if (SDL_HasIntersection(&player, &element))
    //         return 0;
    //      }
    //    }
    // }

     for (i = 0; i < INLINE_MATRIX; ++i) {
        if (!game_info->map_destroyable[i].exist && !game_info->map_destroyable[i].bomb)
          continue;
        const SDL_Rect element = {game_info->map_destroyable[i].x, game_info->map_destroyable[i].y, PIXEL_SIZE, PIXEL_SIZE};
        if (SDL_HasIntersection(&player, &element))
          return 0;
     }

     // Loop over players
     for (y = 0; y < (int)(sizeof(game_info->players)/sizeof(game_info->players[0])); ++y) {
        if (game_info->players->num_player != num_player && &game_info->players[y] != NULL)
        {
          //printf("\nin players stuff\n");
          const SDL_Rect other_player = {game_info->players[y].x, game_info->players[y].y, PIXEL_SIZE, PIXEL_SIZE};
          if (SDL_HasIntersection(&player, &other_player))
            return 0;
        }
      }

   printf("\nBoth iterations done, check_collision done\n");
   return 1;
 }
