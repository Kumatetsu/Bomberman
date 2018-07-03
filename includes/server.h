/*
** server.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Tue Jul  3 22:28:40 2018 hochar_n
** Last update Tue Jul  3 22:29:22 2018 hochar_n
*/

#ifndef	_SERVER_
#define _SERVER_

#include "player.h"
#include "player_info.h"
#include "request.h"


# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2
# define WAITING   3
# define CONNECTED 4
# define MAX_FD 255
# define BUFF_SIZE 1024
# define PORT 4022

typedef struct		s_srv
{
  int			fd;
  int			*tick;
  t_player_info		*players[4];
  fd_set		fd_read;
  t_player_request	*requests[8];
  int			fd_max;
  int			n_players;
}			t_srv;

int	init_server();
int	accept_players(t_srv **srv);
int	add_player(t_srv **s, int fd);
int	create_server_socket();

#endif
