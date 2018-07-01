/*
** main_loop.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Sun Jul  1 23:23:07 2018 hochar_n
*/

#include <stdio.h>
#include "server.h"
#include "request.h"

int                     main_loop(t_srv **srv)
{
    int                 i;
    int                 error;
    socklen_t           len;
    int                 retval;
    t_player_request    *player_request;

    i = 0;
    FD_ZERO(&(*srv)->fd_read);
    (*srv)->fd_max = (*srv)->fd;
    FD_SET((*srv)->fd, &(*srv)->fd_read);
    while ((*srv)->clients[i] != NULL)
    {
        FD_SET((*srv)->clients[i]->fd, &(*srv)->fd_read);
        if ((*srv)->clients[i]->fd > (*srv)->fd_max)
            (*srv)->fd_max = (*srv)->clients[i]->fd;
        i++;
    }
    printf("Before select");
    if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
        return (0);
    printf("after select");
    if (FD_ISSET((*srv)->fd, &(*srv)->fd_read)){
        printf("before accept_clients\n");
        if (accept_clients(srv) == -1)
            return 0;
        printf("%d\n", (*srv)->clients[i]->fd);
    }

    printf("before client action\n");
    for (i = 0; i < 4; i++)
    {
        printf("loop on clients\n");
        if ((*srv)->clients[i] != NULL)
        {
            printf("client before send request\n");
            printf("%d\n", (*srv)->clients[i]->fd);
	        error = 0;
            len = sizeof (error);
            retval = getsockopt ((*srv)->clients[i]->fd, SOL_SOCKET,
                    SO_ERROR, &error, &len);

            if (retval != 0 || error != 0) {
                (*srv)->clients[i] = NULL;
                continue;
            }

            if (FD_ISSET((*srv)->clients[i]->fd, &(*srv)->fd_read))
            {
                int n = 0;
                char buffer[1024];
                if ((n = recv((*srv)->clients[i]->fd, buffer, 1024 - 1, 0))
		    < 0)
                {
                   perror("recv()");
                   player_request = request_deserialize(buffer);
		            printf("%s", request_serialization(player_request));
		            add_request_to_server(srv, player_request);
                   if ( player_request->checksum !=
			get_request_checksum(player_request))
                   {
                       close((*srv)->clients[i]->fd);
                       (*srv)->clients[i] = NULL;

                   }
                   n = 0;
                }

                buffer[n] = 0;
                printf("client send request\n");
            }
        }
    }

    return (1);
}

void	*threaded_main_loop(void *server)
{
  t_srv	**srv;

  srv = (t_srv**)server;
  while (1) { main_loop(srv); }
}

void add_request_to_server(t_srv **srv, t_player_request *player_request)
{
    int i;

    for (i = 0; i < 7; ++i)
    {
        if ((*srv)->requests[i] != NULL)
            continue;
        (*srv)->requests[i] = player_request;
    }
}
