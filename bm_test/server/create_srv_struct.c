/*
** create_srv_struct.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Tue Jun 26 17:36:48 2018 BILLAUD Jean
*/

#include <stdlib.h>
#include <stdio.h>
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
    for (i = 0; i < 8; i++)
    {
        s->requests[i] = NULL;
    }

    return s;
}
