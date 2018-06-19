#include <stdio.h>
#include "server.h"

int main_loop(t_srv **srv)
{
    int i;

    i = 0;

    FD_ZERO(&(*srv)->fd_read);
    //int de la socket
    (*srv)->fd_max = (*srv)->fd;

    FD_SET(STDIN_FILENO, &(*srv)->fd_read);
    FD_SET((*srv)->fd, &(*srv)->fd_read);

    while ((*srv)->clients[i] != NULL)
    {
        FD_SET((*srv)->clients[i]->fd, &(*srv)->fd_read);
        if ((*srv)->clients[i]->fd > (*srv)->fd_max)
            (*srv)->fd_max = (*srv)->clients[i]->fd;

        i++;
    }

    if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
        return (0);

    if (FD_ISSET((*srv)->fd, &(*srv)->fd_read))
        if (accept_clients(srv) == -1)
            return 0;

    for (i = 0; i < 4; i++)
    {
        if ((*srv)->clients[i] != NULL)
        {
            if (FD_ISSET((*srv)->clients[i]->fd, &(*srv)->fd_read))
            {
                printf("client send request\n");
            }
        }
    }

    return (1);
}
