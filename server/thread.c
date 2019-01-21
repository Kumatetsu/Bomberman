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
#include <pthread.h>
#include <time.h>
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
// pour sleep
#include "unistd.h"
// pour usleep
#include "time.h"
// for dev
#include "coord_index_swapper.h"

// 1 sec = 1 nano * 10^9 (1 000 000 000)
static t_game_info dumb_static;

void			my_sleep(int sec, int milli)
{
  int			nano;
  struct timespec	req = {0};

  nano = milli * 10000000;
  req.tv_sec = sec;
  req.tv_nsec = nano;
  nanosleep(&req, NULL);
}

void    verify_bomb_explosion(t_map_destroyable *map_destroyable, int tk)
{
  int i;

  for (i = 0; i < INLINE_MATRIX; i++)
    {
      if(!map_destroyable[i].exist)
	continue;
      
      if (map_destroyable[i].start_explode <= tk)
	{
	  printf("\nBOOOOM");
	  map_destroyable[i].bomb = 0;
	  // gestion de l'explosion, exemple:
	  // si start_explode à tick 20 et tick == 20
	  // 20 + 5 > 20 et 25 - 20, explosion stage == 6 - (25 - 20)
	  // si start_explode à tick 20 et tick == 23
	  // 20 + 5 > 23 et 25 - 23, explosion stage == 6 - (25 - 23)
	  // dernier tour:
	  // si start_explode à tick 20 et tick == 24
	  // 20 + 5 > 24 et 25 - 24, explosion stage == 6 - (25 - 24)
	  // si start_explode à tick 20 et tick == 25
	  // 20 + 5 !> 25 et 25 - 20, explosion stage == 0
	  if (map_destroyable[i].start_explode + 5 > tk)
	    {
	      map_destroyable[i].explosion_stage = 6 - ((map_destroyable[i].start_explode + 5) - tk);
	      boom(map_destroyable, i);
	      printf("BOMB DESTROYED, explosion stage : %d \n", map_destroyable[i].explosion_stage);
	    }
	  else
	    {
	      map_destroyable[i].exist = 0;
	      map_destroyable[i].start_explode = 0;
	      map_destroyable[i].explosion_stage = 0;
	    }	      
	}
    }
}

// ticker
void		*threaded_ticker(void *server)
{
  int		i;
  int		j;
  int		*tk;
  int		socket;
  t_srv		**srv;
  t_game_info	*game_info;

  srv = (t_srv**)server;
  tk = (*srv)->tick;
  my_putstr("\nthreaded tick begin!\n");
  game_info = get_game_info();
  while(1 && game_info != NULL)
    {
      printf("\nTick: %d", (*tk));
      usleep(SLEEP * 1000);
      for (i = 0; i < (*srv)->n_players; i++)
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
  printf("\nServer stopped to send game informations\n");
  // probablement pas suffisant comme retour
  return NULL;
}

// la main_loop du server tourne sur un thread
// en l'état, on boucle indéfiniment sur la fonction main_loop
// main_loop retourne
void	*threaded_main_loop(void *server)
{
  t_srv **srv;
  int	check;

  srv = (t_srv **)server;
  while (1) {
    // retourne 0 si erreur sur select ou accept_player
    // retourne 1 si la boucle va au bout, traitement ou non
    check = main_loop(srv);
    printf("\nMain loop exit with code: %d", check);
  }
}
