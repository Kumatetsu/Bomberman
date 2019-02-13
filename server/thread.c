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
void            my_windows_sleep(int milli)
{
	struct timespec req = { milli / 1000, milli % 1000 * 1000000L };
	nanosleep(&req, NULL);
}

#endif

void verify_bomb_explosion(t_map_destroyable *map_destroyable, int tk)
{
  int i;

  for (i = 0; i < INLINE_MATRIX; i++)
  {
    if (!map_destroyable[i].exist)
      continue;

    if (map_destroyable[i].bomb)
    {
      if (map_destroyable[i].start_explode <= tk)
      {
        // boom(map_destroyable, i);
      }
    }
    else
    {
      if (map_destroyable[i].explosion_stage <= 5 && map_destroyable[i].explosion_stage > 0)
      {
        map_destroyable[i].explosion_stage--;
      }
      else if (map_destroyable[i].explosion_stage == 0)
      {
        map_destroyable[i].exist = 0;
        map_destroyable[i].start_explode = 0;
        map_destroyable[i].explosion_stage = 0;
      }
    }
  }
}

void *bomb_thread_func(void *struct_bomb_thread)
{
  t_bomb_thread *bts;
  t_response_bomb_explosion response;
  t_response_end_explosion reset_explosion;
  bts = (t_bomb_thread *)(struct_bomb_thread);
  int i = 0;
  int k = 0;
  int indexes[13];
  t_srv **srv;
#ifdef _WIN32
	int nbBytesSent;
#endif

  srv = bts->srv;
  printf("server index 0 %d", bts->index);
  indexes[0] = bts->index;
  #ifdef _WIN32
    my_windows_sleep(SLEEP * 8);
  #else
    usleep(SLEEP * 10000);
  #endif
		printf("before boom\n");
		fflush(stdout);
  boom(srv, indexes);
	printf("after boom\n");
	fflush(stdout);

  for (i = 0; i < 4; i++)
  {
    response.players[i] = (*srv)->players[i];
  }
  response.id = EXPLOSION;
  for (i = 0; i < 13; i++)
  {
		printf("LE i = %d\n", i);
			fflush(stdout);
		
		printf("passed 1 de i : %d\n", i);
		fflush(stdout);
    response.index[i] = indexes[i];
		printf("passed 2 de i : %d\n", i);
		fflush(stdout);
		if (indexes[i] >= INLINE_MATRIX || indexes[i] < 0) {
			printf("i exit : %d\n", i);
			continue;
		}
    response.explosion[i] = (*srv)->map_destroyable[indexes[i]];
		printf("passed 3 de i : %d\n", i);
		fflush(stdout);

  }
  for (i = 0; i < 4; i++)
  {
		if ((*srv)->players[i].fd == -1)
			continue;
#ifdef _WIN32
		nbBytesSent = 0;
		printf("before sending explosion from server\n");
		fflush(stdout);
		nbBytesSent = send((*srv)->players[i].fd, (void*)&response, sizeof(response), 0);
		printf("after sending explosion from server\n");
		fflush(stdout);
		if (nbBytesSent < 0)
		{
			printf("error sending from bomb_thread_func n°%d \n", WSAGetLastError());
		}
		else {
			printf("send from bomb_thread_func success of %d bytes \n ", nbBytesSent);
		}
#else
		write((*srv)->players[i].fd, &response, sizeof(response));
#endif
  }
  #ifdef _WIN32
    my_windows_sleep(SLEEP * 2);
  #else
    usleep(SLEEP * 10000);
  #endif

  reset_explosion.id = ENDEXPLOSION;

  for (k = 0; k < 13; k++)
  {
		reset_explosion.index[k] = indexes[k];
    if (indexes[k] >= INLINE_MATRIX || indexes[k] < 0)
      continue;
    (*srv)->map_destroyable[indexes[k]].exist = 0;
    (*srv)->map_destroyable[indexes[k]].bomb = 0;
    (*srv)->map_destroyable[indexes[k]].explosion_stage = 0;
    reset_explosion.explosion[k] = (*srv)->map_destroyable[indexes[k]];
  }
  for (i = 0; i < 4; i++)
  {
		if ((*srv)->players[i].fd == -1)
			continue;
#ifdef _WIN32
		nbBytesSent = 0;
		if ((nbBytesSent = send((*srv)->players[i].fd, (void*)&reset_explosion, sizeof(response), 0)) < 0)
		{
			printf("error sending from bomb_thread_func reset_explosion n°%d \n", WSAGetLastError());
		}
		else {
			printf("send from bomb_thread_func success of %d bytes \n ", nbBytesSent);
		}
#else
		write((*srv)->players[i].fd, &reset_explosion, sizeof(response));
#endif
  }
  free(struct_bomb_thread);
  return NULL;
}

// ticker
/*
void *threaded_ticker(void *server)
{
  int		i;
  int		j;
  int		*tk;
  int		socket;
  t_srv		**srv;
  t_game_info	*game_info;

  srv = (t_srv **)server;
  game_info = get_game_info();
  while (1 && game_info != NULL)
  {
    #ifdef _WIN32
      my_windows_sleep(SLEEP);
    #else
      usleep(SLEEP * 1000);
    #endif
    for (i = 0; i < (*srv)->n_players; i++)
    {
      //verify_bomb_explosion(game_info->map_destroyable, *tk);
      //socket = (*srv)->players[i].fd;
      game_info->id_client = i;
      memcpy(&dumb_static.tick_time, &game_info->tick_time, sizeof(int));
      memcpy(&dumb_static.game_status, &game_info->game_status, sizeof(int));
      memcpy(&dumb_static.id_client, &game_info->id_client, sizeof(int));
      memcpy(&dumb_static.nb_client, &(*srv)->n_players, sizeof(int));
      for (j = 0; j < 4; j++)
        memcpy(&dumb_static.players[j], &game_info->players[j], sizeof(t_player_info));
      for (j = 0; j < INLINE_MATRIX; j++)
        memcpy(&dumb_static.map_destroyable[j], &game_info->map_destroyable[j],
        sizeof(t_map_destroyable));
      #ifdef _WIN32
          send(socket, (void*)&dumb_static, sizeof(dumb_static), 0);
      #else
          write(socket, &dumb_static, sizeof(t_game_info) + 1);
      #endif
    }
      ++(*tk);
      game_info->tick_time = (*tk);
  }
  printf("\nServer stopped to send game informations\n");
  // probablement pas suffisant comme retour
  return NULL;
}
*/
// la main_loop du server tourne sur un thread
// en l'état, on boucle indéfiniment sur la fonction main_loop
// main_loop retourne
void *threaded_main_loop(void *server)
{
  t_srv **srv;
  int check = 1;

  srv = (t_srv **)server;
  while (check)
  {
    // retourne 0 si erreur sur select ou accept_player
    // retourne 1 si la boucle va au bout, traitement ou non
    check = main_loop(srv);
  }
  return NULL;
}
