#ifndef	_SERVER_
#define _SERVER_

# define	FD_FREE 0
# define	FD_CLIENT 1
# define	FD_SERVER 2
# define	WAITING   3
# define	CONNECTED 4
# define	MAX_FD 255
# define	BUFF_SIZE 1024
# define	PORT 4022

#include	"sdl.h"
#include 	"player.h"

typedef struct 	s_server
{
  int		server_fd;
  int		state;
  t_player	*players;
}		t_server;



t_server	*create_server();
void		init_server(t_sdl *sdl);
void		init_socket(t_server **server);
void add_player	(t_server **s, int fd);
#endif
