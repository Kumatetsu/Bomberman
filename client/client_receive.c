/*
** client_get_game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Mon Jul  2 16:17:01 2018 BILLAUD Jean
** Last update Wed Jul  4 10:16:22 2018 MASERA Mathieu
*/

#include "system.h"
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
#include "draw_players.h"
#include "base_map_manager.h"
#include "client_receive.h"
#include "server_request.h"
#include "command_interpretor.h"

void		*listen_server(void *s)
{
  int		i;
  t_thread	*struct_thread;
  int		quit = 0;
  fd_set	fd_read;

  /* 
  ** temporary game info allocated and freed at each loop turn
  ** independant from the server game info 
  */
  t_game_info	*client_game_info;
  t_data		*data;

  struct_thread = (t_thread *)(s);
  data = struct_thread->data;
  if ((client_game_info = malloc(sizeof(t_game_info))) == NULL) {
    printf("\nGameInfo memory allocation failed\n");
    return NULL;
  }

  for (i = 0; i < INLINE_MATRIX; i++)
    {
      client_game_info->map_destroyable[i].y = 0;
      client_game_info->map_destroyable[i].x = 0;
      client_game_info->map_destroyable[i].bomb = 0;
      client_game_info->map_destroyable[i].bomb_owner = -1;
      client_game_info->map_destroyable[i].dying = 0;
      client_game_info->map_destroyable[i].start_explode = 0;
      client_game_info->map_destroyable[i].wall_destroyable = 0;
      client_game_info->map_destroyable[i].exist = 0;
    }

  // construit le model fixe et render copy une premiere fois
  if (!draw_fixed_map(data)) {
    printf("\nFailed to draw fixed map\n");
    quit = 1;
  }
 
  while (!quit)
    {
      FD_ZERO(&fd_read);
      FD_SET(struct_thread->socket, &fd_read);

      printf("\nbefore select\n");
      if (select((struct_thread->socket + 1), &fd_read, NULL, NULL, NULL) == -1) {
	quit = 1;
      }
      if (FD_ISSET(struct_thread->socket, &fd_read) != 0) {
	if (!get_message(struct_thread->socket, &client_game_info)) {
	  quit = 1;
	  continue;
	}
	if (client_game_info->game_status == ENDGAME) {
	  quit = 1;
	}
	for (i = 0; i < INLINE_MATRIX; i++)
	  {
	    data->map_destroyable[i] = client_game_info->map_destroyable[i];
	  }
	SDL_RenderClear(data->renderer);
	// call back the render_copy on the model
	rebuild_map(data);
	/*
	** define the model of player placement 
	** from the new server information done by the render_copy
	*/
	draw_destroyable_model(data);
	if (!draw_players(data, client_game_info)) {
	    printf("\nFailed to draw players\n");
	    quit = 1;
	    continue;
	  }

	/*
	** draw the destroyable and so the bombs
	** fill the model in the map_destroyable
	** draw_destroyable_model(data);
	** call SDL_RenderCopy on map_destroyable
	*/
	build_destroyables(data);
	// draw what is contained in the renderer in the windows
	SDL_RenderPresent(data->renderer);
	SDL_SetRenderTarget(data->renderer, NULL);
      }
    }
  free(client_game_info);
  pthread_exit(NULL);
  return (NULL);
}

int			get_message(SOCKET s, t_game_info **client_game_info)
{
  int			r;
  t_response_pool	response;

#ifdef _WIN32
  r = recv(s, (char*)&response, sizeof(t_response_pool), 0);
#else
  r = recv(s, &response, sizeof(t_response_pool), 0);
#endif
  /*
  ** here we receive the buffer from the server
  ** we send it to the client interpretor so it call the needed function
  ** that will work on the client view
  */
  if (r > 0) {
    printf("client: server response\n");
    printf("response_type %d\n", response.id);
    printf("nb_bytes received : %d\n", r);
    fflush(stdout);
    client_interpretor(client_game_info, &response);
    return (1);
  } else {
    return (0);
  }
}
