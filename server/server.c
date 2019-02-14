/*
** server.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 00:14:25 2018 MASERA Mathieu
** Last update Wed Jul  4 09:28:54 2018 MASERA Mathieu
*/

#include "system.h"
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "map.h"
#include "data.h"
#include "server.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"
#include "static_wall_rect.h"

// Initialise the server after a click on 'create server' in the menu.c
void		*init_server()
{
  SOCKET	s;
  int		i;
  t_srv		*srv;
  pthread_t	main_thread;
  t_game_info	*game_info;

  // initialisation of the server structure and the server socket

  if ((srv = malloc(sizeof(*srv))) == NULL) {
    printf("error allocation memory serveur");
    return (NULL);
  }


#ifdef _WIN32
  if ((s = create_server_socket()) == INVALID_SOCKET) {
    printf("error create server socket : %d\n", WSAGetLastError());
    return (NULL);
  }
#else
  if ((s = create_server_socket()) == -1) {
    printf("error socket init\n");
    return (NULL);
  }
#endif

  srv->fd = s;
  srv->fd_max = s;
  printf("\nInitial server fd and fd_max: %d\n", s);
  srv->n_players = 0;
  srv->game_status = WAITING;

  game_info = calloc(1, sizeof(t_game_info));
  if (game_info == NULL) {
    printf("error allocation memory game_info");
    return (NULL);
  }
  set_game_info(game_info);

  for (i = 0; i < INLINE_MATRIX; i++)
  {
    srv->map_destroyable[i].y = 0;
    srv->map_destroyable[i].x = 0;
    srv->map_destroyable[i].bomb = 0;
    srv->map_destroyable[i].bomb_owner = -1;
    srv->map_destroyable[i].dying = 0;
    srv->map_destroyable[i].start_explode = 0;
    srv->map_destroyable[i].wall_destroyable = 0;
    srv->map_destroyable[i].exist = 0;
  }
  init_wall_rect();
  // we set all the players to unconnected
  for (i = 0; i < 4; i++)
    {
      srv->players[i].connected = 0;
      srv->players[i].num_player = i;
      srv->players[i].fd = -1;
    }
  if (pthread_create(&main_thread, NULL, threaded_main_loop, &srv) != 0) {
      printf("error thread main loop");
      return (NULL);
    }
  pthread_join(main_thread, NULL);
  return (NULL);
}


int			create_server_socket()
{
  SOCKET		s;
  SOCKADDR_IN		sin;
  int			port;

  memset(&sin, 0, sizeof (SOCKADDR_IN));
  s = socket(PF_INET, SOCK_STREAM, 0);

#ifdef _WIN32
  if (s == INVALID_SOCKET) {
    printf("error socket init : %d\n", WSAGetLastError());
    return (-1);
  }
#else
  if (s == -1) {
    printf("error socket init\n");
    return (-1);
  }
#endif

  port = PORT;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (SOCKADDR *)&sin, sizeof(sin)) != 0) {
#ifdef _WIN32
      printf("error socket binding : %d\n", WSAGetLastError());
#else
      printf("error socket binding\n");
#endif
      return (-1);
    }
  if (listen(s, 42) != 0) {
#ifdef _WIN32
    printf("error serveur listening : %d\n", WSAGetLastError());
#else
    printf("error serveur listening\n");
#endif
    return (-1);
  }
  return (s);
}

// return 1 if there is more than 4 players
int server_is_full(t_srv **srv)
{
  if ((*srv)->n_players >= 4) {
    return (1);
  }
  return (0);
}

// define is the server can launch the game
int is_enought_players(t_srv **srv)
{
  if ((*srv)->n_players >= 2 && (*srv)->n_players < 5) {
    return (1);
  }
  return (0);
}

// set_fd_max define the srv->fd_max by reference
void	set_fd_max(t_srv **srv)
{
  int	i;

  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
        {
          FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
          if ((*srv)->players[i].fd > (*srv)->fd_max) {
            (*srv)->fd_max = (*srv)->players[i].fd;
	  }
        }
    }
}
