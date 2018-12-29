/*
** client_get_game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Mon Jul  2 16:17:01 2018 BILLAUD Jean
** Last update Wed Jul  4 10:16:22 2018 MASERA Mathieu
*/

#include <pthread.h>
#include "enum.h"
#include "sdl.h"
#include "client.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "my_put.h"
#include "map.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "data.h"
#include "thread.h"
#include "base_map_manager.h"
#include "move_player.h"
#include "client_receive.h"

void            *listen_server(void *s)
{
  t_thread	*struct_thread;
  int           quit = 0;
  fd_set        fd_read;

  struct_thread= (t_thread *)(s);
  while (!quit)
    {
      FD_ZERO(&fd_read);
      FD_SET(struct_thread->socket, &fd_read);
      printf("\nbefore select\n");
      if (select((struct_thread->socket + 1), &fd_read, NULL, NULL, NULL) == -1)
              quit = 1;
      if (FD_ISSET(struct_thread->socket, &fd_read))
        {
	  if (get_message(struct_thread->socket) == 0)
	    quit = 1;
	  game_info = get_game_info();
	  for (i = 0; i < INLINE_MATRIX; i++)
	    data->map_destroyable[i] = game_info->map_destroyable[i];
	  SDL_RenderClear(data->renderer);
	  // redéfini le model de la map fixe dans array_map
	  draw_all(data);
	  // rebuild le model dans array_map
	  rebuild_map(data);

	  // fonction cheloue:
	  // move_player_stop(data);

	  // dessine les 'destroyables' pour l'instant les bombs
	  // rempli le model dans map_destroyable
	  draw_destroyable_model(data);
	  // appel SDL_RenderCopy sur map_destroyable
    if (game_info != NULL)
    {
      for (i = 0; i < 4; i++)
	{
	  if (game_info->players[i].connected && game_info->players[i].alive)
	    draw_player(data, game_info->players[i]);
	}
    }
	  build_destroyables(data);
	  // dessine le contenu du renderer dans la window
	  SDL_RenderPresent(data->renderer);
	  SDL_SetRenderTarget(data->renderer, NULL);
	}
    }
  pthread_exit(NULL);
}

int get_message(int s)
{
  char buff[sizeof(t_game_info)];
  int r;
  t_game_info *game_info;
  int i;

  game_info = NULL;
  r = recv(s, buff, sizeof(t_game_info) - 1 , 0);
  if (r > 0)
  {
    //deserialize_game_info(buff);
    game_info = (t_game_info*)buff;
    set_game_info(game_info);
    //game_info = get_game_info();
    printf("tick_time %d \n", game_info->tick_time);
    for (i=0; i<4; i++) {
      //      if (&game_info->players[i])
	//      printf("client fd %d\n\n", (int)game_info->players[i].fd);
    }
    return 1;
  }
  else
    return 0;
}
