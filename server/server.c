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
  t_game_info	*game_info;

  tick = 0;
  if ((srv = malloc(sizeof (*srv))) == NULL)
    return (NULL);
  if ((s = create_server_socket()) == -1)
    return (NULL);
  srv->fd = s;
  srv->tick = &tick;
  srv->n_players = 0;
  game_info = calloc(1, sizeof(t_game_info));
  set_game_info(game_info);
  for (i = 0; i < 4; i++)
    srv->players[i] = NULL;
  for (i = 0; i < 8; i++)
    srv->requests[i] = NULL;
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

int		add_player(t_srv **srv, int fd)
{
  t_player_info	*new_player;

  if ((new_player = malloc(sizeof (*new_player))) == NULL)
    return (0);
  new_player->connected = 0;
  new_player->alive = 1;
  new_player->dying = 0;
  new_player->x_pos = 0;
  new_player->y_pos = 0;
  new_player->current_dir = 0;
  new_player->bomb_left = 3; // ?
  new_player->fd = fd;
  new_player->num_player = (*srv)->n_players + 1;
  /**
   ** IL MANQUE SDL_Rect bomber_sprites[5][4]; à instancier dans le t_player
   */
  (*srv)->players[(*srv)->n_players] = new_player;
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

void		process_requests(t_srv **server)
{
  int		i;
  t_game_info	*game_info;

  game_info = get_game_info();
  for (i = 0; i < 8; ++i)
  {
    if ((*server)->requests[i] == NULL)
      continue;
    if ((*server)->requests[i]->command == START_GAME)
    {
      if ((*server)->n_players >= 2 && (*server)->n_players <= 4)
      {
        create_game_info(server);
        my_putstr("\n creation of game requested");
      }
    }
    else if (game_info->game_status == 0)
    {
      free((*server)->requests[i]);
      continue;
    }
    handle_requests(game_info, (*server)->requests[i]);
    free((*server)->requests[i]);
  }
}
