#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "my_put.h"
#include "request.h"
#include "player_info.h"
#include "server.h"
#include "sdl.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "main_loop.h"
#include "thread.h"

// 1 sec = 1 nano * 10^9 (1 000 000 000)  
void			my_sleep(int sec, int milli)
{
  int			nano;
  struct timespec	req = {0};

  nano = milli * 1000000;
  req.tv_sec = sec;
  req.tv_nsec = nano;
  nanosleep(&req, NULL);
}

void	*threaded_ticker(void *server)
{
  char	log[50];
  t_srv **srv;
  int	*tk;
  int   socket;
  char	*serialized_game_info;
  int	i;
  
  srv = (t_srv**)server;
  tk = (*srv)->tick;
  my_putstr("\nthreaded tick begin!\n");
  while(1)
    {
      sprintf(log, "\nTick: %d", (*tk));
      my_putstr(log);
      sprintf(log, "\n number of clients: %d\n", (*srv)->n_players);
      my_putstr(log);
      my_sleep(0, 5000);
      for (i = 0; i < (*srv)->n_players; i++)
	{
	  socket = (*srv)->players[i]->fd;
	  serialized_game_info = serialize_game_info();
	  write(socket, serialized_game_info, sizeof(serialized_game_info + 1));
	}
      ++(*tk);
    }
}

void	*threaded_main_loop(void *server)
{
  t_srv **srv;

  srv = (t_srv **)server;
  while (1) { main_loop(srv); }
}
