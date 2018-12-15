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
#include "my_put.h"
#include "sdl.h"
#include "enum.h"
#include "map.h"
#include "request.h"
#include "player_info.h"
#include "data.h"
#include "server.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "main_loop.h"
#include "thread.h"

// 1 sec = 1 nano * 10^9 (1 000 000 000)
static t_game_info dumb_static;

void			my_sleep(int sec, int milli)
{
  int			nano;
  struct timespec	req = {0};

  nano = milli * 1000000;
  req.tv_sec = sec;
  req.tv_nsec = nano;
  nanosleep(&req, NULL);
}

// ticker
void		*threaded_ticker(void *server)
{
  char		log[50];
  t_srv		**srv;
  int		*tk;
  int		socket;
  //char		*serialized_game_info;
  t_game_info	*game_info;
  int		i;
  int   j;
  int   k;

  srv = (t_srv**)server;
  tk = (*srv)->tick;
  my_putstr("\nthreaded tick begin!\n");
  game_info = get_game_info();
  while(1)
    {
      sprintf(log, "\nTick: %d", (*tk));
      my_putstr(log);
      my_sleep(0, 5000);
      for (i = 0; i < (*srv)->n_players; i++) {
        socket = (*srv)->players[i].fd;
        game_info->id_client = i;
        // set_game_info(game_info);
        memcpy(&dumb_static.checksum, &game_info->checksum, sizeof(int));
        memcpy(&dumb_static.tick_time, &game_info->tick_time, sizeof(int));
        memcpy(&dumb_static.game_status, &game_info->game_status, sizeof(int));
        memcpy(&dumb_static.id_client, &game_info->id_client, sizeof(int));
        memcpy(&dumb_static.nb_client, &(*srv)->n_players, sizeof(int));
        for (k=0; k<4; k++){
          memcpy(&dumb_static.players[k], &game_info->players[k], sizeof(t_player_info));
        }
        for (k=0; k<14; k++){
          for (j=0; j<15; j++){
            memcpy(&dumb_static.map_destroyable[k][j], &game_info->map_destroyable[k][j], sizeof(t_map_destroyable));
          }
        }
        write(socket, &dumb_static, sizeof(t_game_info) + 1);
      }
      ++(*tk);
      game_info->tick_time=(*tk);
    }
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
    printf("\n\nMain loop exit with code: %d\n", check);
  }
}
