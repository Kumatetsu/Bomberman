#ifndef	_SERVER_
#define _SERVER_

#include "player.h"

# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define WAITING   3
# define CONNECTED 4
# define MAX_FD 255
# define BUFF_SIZE 1024
# define PORT 4022

typedef struct 	s_srv
{
  int		fd;
  int		*tick;
  t_player_info	*players[4];
  fd_set	fd_read;
  int		fd_max;
  int		n_players;
}		t_srv;

int	init_server(/*t_sdl *sdl*/);
int	accept_players(t_srv **srv);
int	add_player(t_srv **s, int fd);
int	create_server_socket();

#endif
