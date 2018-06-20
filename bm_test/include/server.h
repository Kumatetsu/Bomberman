#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "player.h"
#include "game_info.h"

typedef struct      s_srv
{
    int             fd;
    t_player_infos	*clients[4];
    fd_set			fd_read;
    int				fd_max;
}                   t_srv;


t_srv           *create_struct_srv();
int             main_loop(t_srv **srv);
int             accept_clients(t_srv **srv);
t_player_infos	*create_player(int fd);

#endif
