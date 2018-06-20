#include <stdlib.h>
#include "server.h"

t_srv_client    *create_srv_client(int fd)
{
    t_srv_client *cli;

    if ((cli = malloc(sizeof (*cli))) == 0)
        return NULL;

    cli->fd = fd;
    cli->magic = fd + 42;
    return cli;
}
