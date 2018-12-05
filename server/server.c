/*
** server.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 00:14:25 2018 MASERA Mathieu
** Last update Wed Jul  4 09:28:54 2018 MASERA Mathieu
*/
<<<<<<< HEAD

#include "system.h"
#include "enum.h"
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

// Initialise le server apres un click sur 'create server' dans menu.c
void		*init_server()
=======
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
>>>>>>> clean repo?
{
  int		s;
  int		i;
  t_srv		*srv;
  int		tick;
  pthread_t	main_thread;
  pthread_t	tick_thread;
  t_game_info	*game_info;

  tick = 0;
<<<<<<< HEAD
  // initialisation de la structure server et de la socket du server
=======
>>>>>>> clean repo?
  if ((srv = malloc(sizeof (*srv))) == NULL)
    return (NULL);
  if ((s = create_server_socket()) == -1)
    return (NULL);
  srv->fd = s;
<<<<<<< HEAD
  srv->fd_max = s;
  printf("\nInitial server fd and fd_max: %d\n", s);
=======
>>>>>>> clean repo?
  srv->tick = &tick;
  srv->n_players = 0;

  game_info = calloc(1, sizeof(t_game_info));
  if (game_info == NULL)
    return (NULL);
<<<<<<< HEAD
 
  set_game_info(game_info);

  init_wall_rect();
  // on set tout les player a 'non connecté'
  for (i = 0; i < 4; i++)
    {
      srv->players[i].connected = 0;
      srv->players[i].num_player = i;
    }
  // on initialise le bench de request à NULL
  for (i = 0; i < 8; i++)
    srv->requests[i] = NULL;
  // on lance les 2 threads: la main loop du serveur et le ticker
=======
  set_game_info(game_info);

  for (i = 0; i < 4; i++)
    srv->players[i].connected = 0;
  for (i = 0; i < 8; i++)
    srv->requests[i] = NULL;
>>>>>>> clean repo?
  if (pthread_create(&tick_thread, NULL, threaded_ticker, &srv) == -1)
    return (NULL);
  if (pthread_create(&main_thread, NULL, threaded_main_loop, &srv) == -1)
    return (NULL);
<<<<<<< HEAD
=======
  //n'attend qu'un client pour qu'on puisse tester tranquillement
  //on doit init le server avant d'écouter les connections
  // if (accept_clients(&srv) == -1)
  //   return 0;

  // PROVIENT DE OLD_SERVER.c dans le folder old/
  // sdl->server_welcome = NULL;

>>>>>>> clean repo?
  pthread_join(tick_thread, NULL);
  pthread_join(main_thread, NULL);
  return (NULL);
}

<<<<<<< HEAD
=======
int		add_player(t_srv **srv, int fd)
{
  t_player_info	new_player;

  new_player.connected = 0;
  new_player.alive = 1;
  new_player.dying = 0;
  new_player.x_pos = 0;
  new_player.y_pos = 0;
  new_player.current_dir = 0;
  new_player.bomb_left = 1;
  new_player.fd = fd;
  new_player.num_player = (*srv)->n_players + 1;
  /**
   ** IL MANQUE SDL_Rect bomber_sprites[5][4]; à instancier dans le t_player
   */
  (*srv)->players[(*srv)->n_players] = new_player;
  (*srv)->n_players++;
  printf("player added");
  return (1);
}
>>>>>>> clean repo?

int			create_server_socket()
{
  int			s;
  struct sockaddr_in	sin;
  int			port;

  memset(&sin, 0, sizeof (struct sockaddr_in));
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  port = PORT;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) == -1)
    return (-1);
  if (listen(s, 42) == -1)
    return (-1);
  return (s);
}

<<<<<<< HEAD
// retourne 1 si il y a plus de 4 joueurs
int     server_is_full(t_srv **srv)
{
  if ((*srv)->n_players >= 4)
    return 1;
  return 0;
}

// défini si le serveur peut lancer la partie
int     is_enought_players(t_srv **srv)
{
  if ((*srv)->n_players >= 2 && (*srv)->n_players < 5)
    return 1;
  return 0;
}

// set_fd_max définis le srv->fd_max par référence
void    set_fd_max(t_srv **srv)
{
  int   i;

  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
        {
          FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
          if ((*srv)->players[i].fd > (*srv)->fd_max)
            (*srv)->fd_max = (*srv)->players[i].fd;
        }
    }
=======
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
      (*server)->requests[i] = NULL;
      continue;
    }
    handle_requests(game_info, (*server)->requests[i]);
    free((*server)->requests[i]);
    (*server)->requests[i] = NULL;
  }
>>>>>>> clean repo?
}
