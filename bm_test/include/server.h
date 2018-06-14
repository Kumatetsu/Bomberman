#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct  s_srv_client
{
    int         fd;
    unsigned int magic;
}               t_srv_client;

typedef struct      s_srv
{
    int             fd;
    t_srv_client    *clients[4];
    fd_set			fd_write;
    fd_set			fd_read;
    int				fd_max;
}                   t_srv;


t_srv           *create_struct_srv();
// int             main_loop(t_srv **srv);
int             accept_clients(t_srv **srv);
t_srv_client    *create_srv_client(int fd);

#endif
