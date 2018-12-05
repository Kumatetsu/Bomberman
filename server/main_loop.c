/*
** main_loop.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:37:32 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:33 2018 MASERA Mathieu
*/

#include <stdio.h>
#include "player_info.h"
#include "server.h"
#include "request.h"
#include "game_info.h"
#include "main_loop.h"
#include "my_put.h"

int			main_loop(t_srv **srv)
{
  int			i;
  int			error;
  socklen_t		len;
  int			retval;
  t_player_request	*player_request;
  t_game_info		*game_info;

  i = 0;
  game_info = get_game_info();
  FD_ZERO(&(*srv)->fd_read);
  (*srv)->fd_max = (*srv)->fd;
  FD_SET((*srv)->fd, &(*srv)->fd_read);
  while (i < 4 && (*srv)->players[i].connected == 1)
    {
      FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
      if ((*srv)->players[i].fd > (*srv)->fd_max)
	(*srv)->fd_max = (*srv)->players[i].fd;
      i++;
    }
  if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
    return (0);
  if (FD_ISSET((*srv)->fd, &(*srv)->fd_read)){
    if (accept_players(srv) == -1)
      return 0;
  }
  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
        {
	  error = 0;
	  len = sizeof (error);
	  retval = getsockopt ((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, &error, &len);
	  if (retval != 0 || error != 0) {
	    (*srv)->players[i].connected = 0;
	    continue;
	  }
	  if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read))
            {
	      int n = 0;
	      char buffer[sizeof(t_game_info)];
	      if((n = recv((*srv)->players[i].fd, buffer, sizeof(t_game_info), 0)) < 0)
                {
		  perror("recv()");
		  player_request = request_deserialize(buffer);
		  handle_requests(game_info, player_request);
		  printf("%s", request_serialization(player_request));
      my_putstr("GET REQUEST DUMB DUMB\n\n\n\n\n");
		  if (player_request->checksum != get_request_checksum(player_request))
		    {
		      close((*srv)->players[i].fd);
		      (*srv)->players[i].connected = 0;
		    }
		  n = 0;
                }
	      buffer[n] = 0;
	      printf("client send request\n");
            }
        }
    }
  // process_requests(srv);
  return (1);
}
