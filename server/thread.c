/*
** thread.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:39:24 2018 MASERA Mathieu
** Last update Wed Jul  4 09:39:25 2018 MASERA Mathieu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#ifdef linux
#include "time.h"
#endif

#ifdef _WIN32
#include "windows_nanosleep.h"
#define HAVE_STRUCT_TIMESPEC
#endif
// for dev

#include <pthread.h>
#include "coord_index_swapper.h"

// 1 sec = 1 nano * 10^9 (1 000 000 000)
static t_game_info dumb_static;

#ifdef _WIN32
void            my_windows_sleep(int milli)
{
	int			nano;

	nano = milli * 1000000;
	nanosleep((LONGLONG)nano);
}
#endif

#ifdef linux
void			my_sleep(int sec, int milli)
{
  int nano;
  struct timespec req = {0};

  nano = milli * 10000000;
  req.tv_sec = sec;
  req.tv_nsec = nano;
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

  srv = bts->srv;
  printf("server index 0 %d", bts->index);
  indexes[0] = bts->index;
  usleep(SLEEP * 10000);
  boom(srv, indexes);
  for (i = 0; i < 4; i++)
  {
    response.players[i] = (*srv)->players[i];
  }
  response.id = EXPLOSION;
  for (i = 0; i < 13; i++)
  {
    if (indexes[i] > 194)
      continue;
    response.index[i] = indexes[i];
    response.explosion[i] = (*srv)->map_destroyable[indexes[i]];
  }
  for (i = 0; i < 4; i++)
  {
    write((*srv)->players[i].fd, &response, sizeof(response));
  }
  usleep(SLEEP * 10000);
  reset_explosion.id = ENDEXPLOSION;
  for (k = 0; k < 13; k++)
  {
    if (indexes[k] > 194)
      continue;
    (*srv)->map_destroyable[indexes[k]].exist = 0;
    (*srv)->map_destroyable[indexes[k]].bomb = 0;
    (*srv)->map_destroyable[indexes[k]].explosion_stage = 0;
    reset_explosion.explosion[k] = (*srv)->map_destroyable[indexes[k]];
    reset_explosion.index[k] = indexes[k];
  }
  for (i = 0; i < 4; i++)
  {
    write((*srv)->players[i].fd, &reset_explosion, sizeof(response));
  }
  free(struct_bomb_thread);
  return NULL;
}

// ticker
void *threaded_ticker(void *server)
{
  int				i;
  int				j;
  int				*tk;
  int				socket;
  t_srv				**srv;
  t_game_info		*game_info;

  srv = (t_srv **)server;
  game_info = get_game_info();
  while (1 && game_info != NULL)
  {
    usleep(SLEEP * 1000);
    for (i = 0; i < (*srv)->n_players; i++)
    {
      printf("\nTick: %d", (*tk));
#ifdef _WIN32
	  my_windows_sleep(SLEEP);
#endif
#ifdef linux
	  my_sleep(0, SLEEP);
#endif
*      for (i = 0; i < (*srv)->n_players; i++)
	{
	  verify_bomb_explosion(game_info->map_destroyable, *tk);
	  socket = (*srv)->players[i].fd;
	  game_info->id_client = i;
	  memcpy(&dumb_static.checksum, &game_info->checksum, sizeof(int));
	  memcpy(&dumb_static.tick_time, &game_info->tick_time, sizeof(int));
	  memcpy(&dumb_static.game_status, &game_info->game_status, sizeof(int));
	  memcpy(&dumb_static.id_client, &game_info->id_client, sizeof(int));
	  memcpy(&dumb_static.nb_client, &(*srv)->n_players, sizeof(int));
	  for (j=0; j<4; j++)
	    memcpy(&dumb_static.players[j], &game_info->players[j], sizeof(t_player_info));
	  for (j=0; j<INLINE_MATRIX; j++)
	    memcpy(&dumb_static.map_destroyable[j], &game_info->map_destroyable[j],
		   sizeof(t_map_destroyable));
	  write(socket, &dumb_static, sizeof(t_game_info) + 1);
	}
      ++(*tk);
      game_info->tick_time = (*tk);
    }
  }
  printf("\nServer stopped to send game informations\n");
  // probablement pas suffisant comme retour
  return NULL;
}

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
