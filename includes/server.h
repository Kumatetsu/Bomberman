/*
** server.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Tue Jul  3 22:28:40 2018 hochar_n
** Last update Tue Jul  3 23:42:26 2018 hochar_n
*/

#ifndef _SERVER_H_
#define _SERVER_H_

// exceptional include
#include <sys/select.h>

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define WAITING 3
#define CONNECTED 4
#define MAX_FD 255
#define BUFF_SIZE 1024
#define PORT 4022

typedef struct s_srv
{
  int fd;
  t_player_info players[4];
  t_map_destroyable map_destroyable[195];
  fd_set fd_read;
  int fd_max;
  int n_players;
  int game_status;
  int running;
} t_srv;

void *init_server();
int create_server_socket();
int server_is_full(t_srv **srv);
int is_enought_players(t_srv **srv);
void set_fd_max(t_srv **srv);
void process_requests(t_srv **srv);

#endif /* !_SERVER_H_ */
