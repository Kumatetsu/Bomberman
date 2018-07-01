#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "socket.h"
#include "server.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"

t_game_info	*create_game(int *fd, int *fd2, int *fd3, int *fd4)
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
  
  //n'attend qu'un client pour qu'on puisse tester tranquillement
  //on doit init le server avant d'écouter les connections
  // if (accept_clients(&srv) == -1)
  //   return 0;
  pthread_join(tick_thread, NULL);
  pthread_join(main_thread, NULL);
  // while(main_loop(&srv));
  return 0;
}
  
