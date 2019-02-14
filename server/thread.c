/*
** thread.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:39:24 2018 MASERA Mathieu
** Last update Wed Jul  4 09:39:25 2018 MASERA Mathieu
*/

#include "system.h"
#include "constant.h"
#include "my_put.h"
#include "sdl.h"
#include "enum.h"
#include "map.h"
#include "client_request.h"
#include "player_info.h"
#include "data.h"
#include "server.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "main_loop.h"
#include "bomb_management.h"
#include "thread.h"
#include "server_request.h"
// pour sleep
#include "unistd.h"
// pour usleep
// for dev
#include "coord_index_swapper.h"

// 1 sec = 1 nano * 10^9 (1 000 000 000)
//static t_game_info dumb_static;

#ifdef _WIN32
void			my_windows_sleep(int milli)
{
  struct timespec	req = { milli / 1000, milli % 1000 * 1000000L };
  nanosleep(&req, NULL);
}
#endif

void	verify_bomb_explosion(t_map_destroyable *map_destroyable, int tk)
{
  int	i;

  for (i = 0; i < INLINE_MATRIX; i++)
    {
      if (!map_destroyable[i].exist) {
	continue;
      }
      if (map_destroyable[i].bomb) {
	if (map_destroyable[i].start_explode <= tk) {
	  // boom(map_destroyable, i);
	}
      } else {
	if (map_destroyable[i].explosion_stage <= 5 && map_destroyable[i].explosion_stage > 0) {
	  map_destroyable[i].explosion_stage--;
	} else if (map_destroyable[i].explosion_stage == 0) {
	  map_destroyable[i].exist = 0;
	  map_destroyable[i].start_explode = 0;
	  map_destroyable[i].explosion_stage = 0;
	}
      }
    }
}

void				*bomb_thread_func(void *struct_bomb_thread)
{
  t_bomb_thread			*bts;
  t_response_bomb_explosion	response;
  t_response_end_explosion	reset_explosion;
  int				indexes[13];
  t_srv				**srv;
  int				i, k;
  
#ifdef _WIN32
  int				nbBytesSent;
#endif

  
  bts = (t_bomb_thread *)(struct_bomb_thread);
  i = 0;
  k = 0;
  srv = bts->srv;
  printf("server index 0 %d", bts->index);
  indexes[0] = bts->index;
#ifdef _WIN32
  my_windows_sleep(SLEEP * 8);
#else
  usleep(SLEEP * 8000);
#endif
  boom(srv, indexes);

  for (i = 0; i < 4; i++)
    {
      response.players[i] = (*srv)->players[i];
    }
  response.id = EXPLOSION;
  for (i = 0; i < 13; i++)
    {
      response.index[i] = indexes[i];
      if (indexes[i] >= INLINE_MATRIX || indexes[i] < 0) {
	continue;
      }
      response.explosion[i] = (*srv)->map_destroyable[indexes[i]];

    }
  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      nbBytesSent = 0;
      nbBytesSent = send((*srv)->players[i].fd, (void*)&response, sizeof(response), 0);
      fflush(stdout);
      if (nbBytesSent < 0) {
	printf("error sending from bomb_thread_func n°%d \n", WSAGetLastError());
      } else {
	printf("send from bomb_thread_func success of %d bytes \n ", nbBytesSent);
      }
#else
      write((*srv)->players[i].fd, &response, sizeof(response));
#endif
    }
#ifdef _WIN32
  my_windows_sleep(SLEEP * 2);
#else
  usleep(SLEEP * 2000);
#endif

  reset_explosion.id = ENDEXPLOSION;
  for (k = 0; k < 13; k++)
    {
      reset_explosion.index[k] = indexes[k];
      if (indexes[k] >= INLINE_MATRIX || indexes[k] < 0) {
	continue;
      }
      (*srv)->map_destroyable[indexes[k]].exist = 0;
      (*srv)->map_destroyable[indexes[k]].bomb = 0;
      (*srv)->map_destroyable[indexes[k]].explosion_stage = 0;
      reset_explosion.explosion[k] = (*srv)->map_destroyable[indexes[k]];
    }
  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].fd == -1) {
	continue;
      }
#ifdef _WIN32
      nbBytesSent = 0;
      if ((nbBytesSent = send((*srv)->players[i].fd, (void*)&reset_explosion, sizeof(response), 0)) < 0) {
	printf("error sending from bomb_thread_func reset_explosion n°%d \n", WSAGetLastError());
      } else {
	printf("send from bomb_thread_func success of %d bytes \n ", nbBytesSent);
      }
#else
      write((*srv)->players[i].fd, &reset_explosion, sizeof(response));
#endif
    }
  free(struct_bomb_thread);
  return (NULL);
}

// The server main loop run on a thread
// in this state, the loop work indefinitely on the main_loop function
void *threaded_main_loop(void *server)
{
  t_srv **srv;
  int check = 1;

  srv = (t_srv **)server;
  while (check)
    {
      // return 0 if error on select or accept_player
      // return 1 if the loop reach the end, treatement or not
      check = main_loop(srv);
    }
  return (NULL);
}
