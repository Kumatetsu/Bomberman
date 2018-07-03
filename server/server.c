#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "sdl.h"
#include "player.h"
#include "socket.h"
#include "thread.h"
#include "request.h"
#include "game_info.h"
#include "my_put.h"
#include "server.h"

void		*init_server() // sdl provient de old/old_server.c
{
  int		s;
  int		i;
  t_srv		*srv;
  int		tick;
  pthread_t	main_thread;
  pthread_t	tick_thread;

  tick = 0;
  if ((srv = malloc(sizeof (*srv))) == NULL)
    return (NULL);
  if ((s = create_server_socket()) == -1)
    return (NULL);
  srv->fd = s;
  srv->tick = &tick;
  srv->n_players = 0;
  for (i = 0; i < 4; i++)
    srv->players[i] = NULL;
  if (pthread_create(&tick_thread, NULL, threaded_ticker, &srv) == -1)
    return (NULL);
  if (pthread_create(&main_thread, NULL, threaded_main_loop, &srv) == -1)
    return (NULL);
  //n'attend qu'un client pour qu'on puisse tester tranquillement
  //on doit init le server avant d'écouter les connections
  // if (accept_clients(&srv) == -1)
  //   return 0;

  // PROVIENT DE OLD_SERVER.c dans le folder old/
  // sdl->server_welcome = NULL;

  pthread_join(tick_thread, NULL);
  pthread_join(main_thread, NULL);
  return (NULL);
}

int			accept_players(t_srv **srv)
{
  int			check;
  int			player_socket;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  check = (*srv)->n_players;
  memset(&client_sin, 0, sizeof (struct sockaddr_in));
  client_sin_len = sizeof (client_sin);
  player_socket = accept((*srv)->fd, (struct sockaddr *)&client_sin, &client_sin_len);
  if (player_socket == -1)
    return (-1);
  if ((*srv)->players[3] != NULL)
    return (0);
  if (!add_player(srv, player_socket))
    return (-1);
  if (check == ((*srv)->n_players) - 1)
    my_putstr("\nPlayer successfully added");
  else
    my_putstr("\nServer failed to add client");
  // retourne 1 si joueur ajouté, 0 sinon
  return ((*srv)->n_players - check);
}

int		add_player(t_srv **srv, int fd)
{
  t_player_info	*new;

  if ((new = malloc(sizeof (*new))) == NULL)
    return (0);
  new->connected = 0;
  new->alive = 1;
  new->dying = 0;
  new->x_pos = 0;
  new->y_pos = 0;
  new->current_dir = 0;
  new->bomb_left = 3; // ?
  new->fd = fd;
  new->num_player = (*srv)->n_players + 1;
  /**
   ** IL MANQUE SDL_Rect bomber_sprites[5][4]; à instancier dans le t_player
   */
  (*srv)->players[(*srv)->n_players] = new;
  (*srv)->n_players++;
  printf("player added");
  return (1);
}

int			create_server_socket()
{
  int			s;
  struct sockaddr_in	sin;
  int			port;

  memset(&sin, 0, sizeof (struct sockaddr_in));
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  port = 4022;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) == -1)
    return (-1);
  if (listen(s, 42) == -1)
    return (-1);
  return (s);
}
