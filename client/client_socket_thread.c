/*
** client_socket_thread.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/client
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 00:13:33 2018 MASERA Mathieu
** Last update Wed Jul  4 10:16:38 2018 MASERA Mathieu
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "sdl.h"
#include "my_put.h"
#include "client.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "thread.h"

void		*thread_listen_serv(void *s)
{
  int		iterator;
  int		socket = *((int *)s);
  int		quit = 0;
  fd_set	fd_read;
  t_game_info	*game_info;

  printf("OK %d", socket);
  while (!quit)
    {
      FD_ZERO(&fd_read);
      FD_SET(socket, &fd_read);
      printf("\nbefore select\n");
      if (select((socket + 1), &fd_read, NULL, NULL, NULL) == -1)
	quit = 1;

      if (FD_ISSET(socket, &fd_read))
        {
	  printf("tata\n");
	  if (get_message(socket) == 0)
            {
	      quit = 1;
            }
	  game_info = get_game_info();
	  for (iterator = 0; iterator < 4; iterator++)
	    {

	      if (game_info->players[iterator].fd != 0)
		{
		  printf("Im player: %d \n", game_info->id_client);
		  //             printf("waaaaaaaaaaa %d num_player \n", game_info->players[0]->num_player);
		}
	    }
        }
    }
  pthread_exit(NULL);
}
