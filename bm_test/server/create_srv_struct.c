#include <stdlib.h>
#include "server.h"

t_srv *create_struct_srv()
{
    t_srv *s;

    if ((s = malloc(sizeof(*s))) == 0)
        return NULL;
    s->fd = 0;

    return s;
}
