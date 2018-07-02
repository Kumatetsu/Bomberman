#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "sdl.h"
#include "client.h"

#include "thread.h"

void *thread_listen_serv(void *s)
{
    int socket = *((int *)s);
    int quit = 0;
    fd_set fd_read;
    printf("OK %d", socket);
    while (!quit)
    {
        FD_ZERO(&fd_read);
        FD_SET(socket, &fd_read);

        if (select((socket + 1), &fd_read, NULL, NULL, NULL) == -1)
            quit = 1;

        if (FD_ISSET(socket, &fd_read))
        {
            printf("tata\n");
            if (get_message(socket) == 0)
            {
                quit = 1;
            }
        }
    }

    pthread_exit(NULL);
}
