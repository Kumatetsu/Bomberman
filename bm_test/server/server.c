/*
** server.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <abel@epitech.eu>
**
** Started on  Sun Jul  1 17:42:55 2018 hochar_n
** Last update Sun Jul  1 18:28:57 2018 hochar_n
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "socket.h"
#include "server.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"

int		main()
{
  int		s;
  t_srv		*srv;
  int		tick;
  pthread_t	main_thread;
  pthread_t	tick_thread;

  tick = 0;
  if ((srv = create_struct_srv()) == NULL)
    return (0);
  if ((s = create_server_socket()) == -1)
    return (0);

  srv->fd = s;
  srv->tick = &tick;
  srv->n_clients = 0;
  if (pthread_create(&tick_thread, NULL, threaded_ticker, &srv) == -1)
    {
      printf("thread tick failed");
      return (0);
    }
  printf("thread tick succeed");
  if (pthread_create(&main_thread, NULL, threaded_main_loop, &srv) == -1)
    {
      printf("main thread failed");
      return (0);
    }
  pthread_join(tick_thread, NULL);
  pthread_join(main_thread, NULL);
  return 0;
}
