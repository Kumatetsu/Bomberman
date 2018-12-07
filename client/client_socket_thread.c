/*
** client_socket_thread.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/client
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 00:13:33 2018 MASERA Mathieu
** Last update Wed Jul  4 10:16:38 2018 MASERA Mathieu
*/

#include "system.h"
#include "sdl.h"
#include "my_put.h"
#include "client.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "thread.h"

void *thread_listen_serv(void *s)
{
  t_thread *struct_thread;
  int		quit = 0;
  fd_set	fd_read;

  struct_thread= (t_thread *)(s);
  while (!quit)
  {
    FD_ZERO(&fd_read);
    FD_SET(socket, &fd_read);
    printf("\nbefore select\n");
    if (select((socket + 1), &fd_read, NULL, NULL, NULL) == -1)
      quit = 1;

    if (FD_ISSET(socket, &fd_read))
    {
      FD_ZERO(&fd_read);
      FD_SET(struct_thread->socket, &fd_read);
      printf("\nbefore select\n");
      if (select((struct_thread->socket + 1), &fd_read, NULL, NULL, NULL) == -1)
	      quit = 1;

      if (FD_ISSET(struct_thread->socket, &fd_read))
        {
	   printf("tata\n");
	    if (get_message(struct_thread->socket) == 0)
           {
	     quit = 1;
           }
        SDL_RenderClear(struct_thread->data->renderer);
        rebuild_map(struct_thread->data);
        move_player_stop(struct_thread->data);
        draw_all(struct_thread->data);
        SDL_RenderPresent(struct_thread->data->renderer);
        SDL_SetRenderTarget(struct_thread->data->renderer, NULL);
	    }
        }
  pthread_exit(NULL);
  return NULL;
}
