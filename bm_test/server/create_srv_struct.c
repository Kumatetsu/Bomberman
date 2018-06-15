#include <stdlib.h>
#include "server.h"

t_srv *create_struct_srv()
{
    t_srv *s;
    int    i;

    if ((s = malloc(sizeof(*s))) == 0)
        return NULL;
    s->fd = 0;

    for (i = 0; i < 4; i++)
    {
        s->clients[i] = NULL;
    }

    return s;
}
