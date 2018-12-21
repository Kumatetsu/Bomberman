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
#include "constant.h"
#include "sdl.h"
#include "bomber_sprites.h"
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
#include "draw_base_map.h"
#include "base_map_manager.h"
#include "move_player.h"
#include "client_receive.h"

void            *listen_server(void *s)
{
  int		i;
  t_thread	*struct_thread;
  int           quit = 0;
  fd_set        fd_read;
  t_game_info	*game_info;
  t_data	*data;
  
  struct_thread= (t_thread *)(s);
  data = struct_thread->data;
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
	    {
	      data->map_destroyable[i] = game_info->map_destroyable[i];
	    }
	  SDL_RenderClear(data->renderer);
	  rebuild_map(data);
	  move_player_stop(data);
	  draw_all(data);
	  draw_destroyable_model(data);
	  //	  build_destroyables(data);
	  SDL_RenderPresent(data->renderer);
	  SDL_SetRenderTarget(data->renderer, NULL);
	}
    }
  pthread_exit(NULL);
}

int		get_message(int s)
{
  char		buff[sizeof(t_game_info) + 1];
  int		r;
  t_game_info	*game_info;
  int		i;

  game_info = NULL;
  r = recv(s, buff, sizeof(t_game_info) + 1, 0);
  if (r > 0)
  {
    //deserialize_game_info(buff);
    game_info = (t_game_info*)buff;
    set_game_info(game_info);
    //game_info = get_game_info();
    printf("tick_time %d received %d bytes\n", game_info->tick_time, r);
    for (i=0; i<4; i++) {
      //      if (&game_info->players[i])
	//      printf("client fd %d\n\n", (int)game_info->players[i].fd);
    }
    return 1;
  }
  else
    return 0;
}
