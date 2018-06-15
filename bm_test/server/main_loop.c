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
        if ((*srv)->clients[i]->fd > (*srv)->fd_max)
            (*srv)->fd_max = (*srv)->clients[i]->fd;

        i++;
    }

    printf("yoyoyoyyo\n");
    return (1);
}
