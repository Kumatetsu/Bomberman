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
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "my_put.h"
#include "map.h"
#include "game_info.h"
#include "moving.h"
#include "coord_index_swapper.h"
#include "collision.h"
#include "base_map_manager.h"
#include "bomb.h"
#include "thread.h"
#include <pthread.h>

/**
 * @params (*)t_game_info
 * @params (*)t_player_request
 * @return 1 -> success 0 -> fail
 **/
t_map_destroyable	*place_bomb(t_srv **srv, int id_player, int linked_index[1])
{
  t_player_info		player;
  int			index;
  t_map_destroyable	*bomb = NULL;
  pthread_t		bomb_thread;
  t_bomb_thread		*struct_bomb_thread;

  bomb = malloc(sizeof(t_map_destroyable));
  if (bomb == NULL) { // If allocation failed
    printf("t_map_destroyable bomb allocation failed\n");
    return NULL;
  }

  printf("\nPLACING BOMB\n");
  player = (*srv)->players[id_player];

  if (player.connected == 0) {
    return (0);
  }

  bomb->exist = 1;

  player.bomb_left--;
  bomb->bomb = 1;

  bomb->bomb_owner = id_player;

  // cohabitation of a principe of pixel and squares
  index = coord_to_index(player.x + 10, player.y + 40);
  switch (player.direction_sprite)
    {
    case bomber_d:
      index = index + COLUMNS;
      // we place under the feet
      break;

    case bomber_l:
      index--;
      /*
	bomb.x = player.x - PIXEL_SIZE;
	// différence de taille entre le SDL_Rect des bombers et celui des bombes (7px * 3)
	bomb.y = player.y + 21;
      */
      break;

    case bomber_r:
      index++;
      /*
	bomb.x = player.x + PIXEL_SIZE;
	// différence de taille entre le SDL_Rect des bombers et celui des bombes (7px * 3)
	bomb.y = player.y + 21;
      */
      break;

    case bomber_u:
      index = index - COLUMNS;
      /*
	bomb.x = player.x;
	bomb.y = player.y - PIXEL_SIZE;
      */
      break;
    default:
      break;
    }
  bomb->x = index_to_x(index);
  bomb->y = index_to_y(index);
  const SDL_Rect zone = init_rect(bomb->x + 20, bomb->y + 20, 2, 2);
  if (has_collision_with_wall(zone)) {
    printf("\nBOMB HAS COLLISION\n");
    return (NULL);
  }
  if ((*srv)->map_destroyable[index].exist) {
    printf("\nYou can't place a bomb here, already one in that case\n");
    return (NULL);
  } else {
    printf("\nPlacing bomb at index: %d, position: %d/%d\n", index, bomb->x, bomb->y);
    (*srv)->map_destroyable[index] = (*bomb);
    if ((struct_bomb_thread = malloc(sizeof(t_bomb_thread))) == NULL) {
      printf("struct_bomb_thread allocation failed\n");
      return (NULL);
    }
    struct_bomb_thread->srv = srv;
    struct_bomb_thread->index = index;
    linked_index[0] = index;
    printf("index before thread: %d", struct_bomb_thread->index);
    if (pthread_create(&bomb_thread, NULL, bomb_thread_func, struct_bomb_thread) != 0) {
      printf("pthread_create bomb_thread_func failed\n");
      return (NULL);
    }
    return (bomb);
  }
}
