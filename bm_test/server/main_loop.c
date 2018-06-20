#include <stdio.h>
#include "server.h"

int main_loop(t_srv **srv)
{
    int i;
    int error;
    socklen_t len;
    int retval;

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
            retval = getsockopt ((*srv)->clients[i]->fd, SOL_SOCKET, SO_ERROR, &error, &len);

            if (retval != 0 || error != 0) {
                (*srv)->clients[i] = NULL;
                continue;
            }

            if (FD_ISSET((*srv)->clients[i]->fd, &(*srv)->fd_read))
            {
                //Ça c'est caca copié collé, pour eviter de boucler sale parce que le job est pas rcv
                int n = 0;
                char buffer[1024];
                if((n = recv((*srv)->clients[i]->fd, buffer, 1024 - 1, 0)) < 0)
                {
                   perror("recv()");
                   /* if recv error we disonnect the client */
                   n = 0;
                }

                buffer[n] = 0;
                printf("client send request\n");
            }
        }
    }

    return (1);
}
