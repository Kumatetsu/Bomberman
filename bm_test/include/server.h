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
#include "request.h"

typedef struct		s_srv
{
  int			fd;
  int			*tick;
  t_player_info		*clients[4];
  fd_set		fd_read;
  int			fd_max;
  int			n_clients;
}			t_srv;


t_srv           *create_struct_srv();
int             main_loop(t_srv **srv);
void		*threaded_main_loop(void *server);
int             accept_clients(t_srv **srv);
t_player_info	*create_player(int fd);
int		check_collision(int** map, t_player_request *player_request);
void		move_player(t_game_info *game_info, t_player_request *player_request, int **map_pointer);
t_game_info *create_game_info(int fd1, int fd2, int fd3, int fd4);
long        random_at_most(long max);
void        specify_player_info(int fd1, int fd2, int fd3, int fd4, int i, t_game_info *game_info);

#endif
