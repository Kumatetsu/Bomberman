/*
** client_get_game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Mon Jul  2 16:17:01 2018 BILLAUD Jean
** Last update Wed Jul  4 10:16:22 2018 MASERA Mathieu
*/

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC
#endif
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
#include "draw_players.h"
#include "base_map_manager.h"
#include "client_receive.h"
#include <stdio.h>

void            *listen_server(void *s)
{
  int		i;
  t_thread	*struct_thread;
  int           quit = 0;
  fd_set        fd_read;
  // game info temporaire allouée
  // et libérée à chaque tour de boucle
  // indépendante de la game_info server
  t_game_info	*client_game_info;
  t_data	*data;

  struct_thread= (t_thread *)(s);
  data = struct_thread->data;
  if ((client_game_info = malloc(sizeof(t_game_info))) == NULL)
    {
      printf("\nGameInfo memory allocation failed\n");
      return NULL;
    }
  // construit le model fixe et render copy une premiere fois
  if (!draw_fixed_map(data))
    {
      printf("\nFailed to draw fixed map\n");
      quit = 1;
    }
  while (!quit)
    {
      FD_ZERO(&fd_read);
#ifdef _WIN32
      FD_SET((unsigned int)struct_thread->socket, &fd_read);
#else
	  FD_SET(struct_thread->socket, &fd_read);
#endif

	  printf("\nbefore select\n");
	  if (select((struct_thread->socket + 1), &fd_read, NULL, NULL, NULL) == -1)
	  {
		  printf("error select listen server");
		  quit = 1;
	  }
      if (FD_ISSET(struct_thread->socket, &fd_read))
        {
	  if (!get_message(struct_thread->socket, client_game_info))
	    {
	      quit = 1;
	      continue;
	    }
	  //printf("\nFreshly updated client_game_info, test on nb_client: %d\n", client_game_info->nb_client);
	  for (i = 0; i < 4; i++)
	    {
	      //	      printf("test on players n°%d: alive: %d, connected: %d\n", client_game_info->players[i].num_player, client_game_info->players[i].alive, client_game_info->players[i].connected);
	    }
	  for (i = 0; i < INLINE_MATRIX; i++)
	    data->map_destroyable[i] = client_game_info->map_destroyable[i];
	  SDL_RenderClear(data->renderer);
	  // rappelle render_copy sur le model
	  rebuild_map(data);
	  // défini le model de placement des players
	  // depuis les nouvelles informations du serveur
	  // effectue le render_copy
	  draw_destroyable_model(data);
	  if (!draw_players(data, client_game_info))
	    {
	      printf("\nFailed to draw players\n");
	      quit = 1;
	      continue;
	    }
	  // fonction cheloue:
	  // move_player_stop(data)

	  // dessine les 'destroyables' pour l'instant les bombs
	  // rempli le model dans map_destroyable
	  // draw_destroyable_model(data);
	  // appel SDL_RenderCopy sur map_destroyable
	  build_destroyables(data);
	  // dessine le contenu du renderer dans la window
	  SDL_RenderPresent(data->renderer);
	  SDL_SetRenderTarget(data->renderer, NULL);
	}
    }
  free(client_game_info);
  pthread_exit(NULL);
  return (NULL);
}

int		get_message(int s, t_game_info *client_game_info)
{
  int		r;
  char		buff[sizeof(t_game_info) + 1];

  r = recv(s, buff, sizeof(t_game_info) + 1, 0);
  // une t_game_info fait plus de 7000 bytes
  // si l'ensemble n'est pas consommé, il peut rester
  // quelques bytes qui seront traités et provoqueront une erreur
  // ici, un système permettant de checké l'intégrité de la
  // game_info serait le bienvenu, c'était la cause du bug de sérialisation
  if (r > 3000)
  {
    *client_game_info = (*(t_game_info*)buff);
    printf("tick_time %d received %d bytes\n", client_game_info->tick_time, r);
    return (1);
  }
  else
    return (0);
}
