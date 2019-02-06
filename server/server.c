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

// Initialise le server apres un click sur 'create server' dans menu.c
void *init_server()
{
  int s;
  int i;
  t_srv *srv;
  pthread_t main_thread;
  // pthread_t	tick_thread;
  t_game_info *game_info;

    tick = 0;
  // initialisation de la structure server et de la socket du server
  if ((srv = (t_srv*)malloc(sizeof(t_srv))) == NULL) {
	  printf("error allocation memory serveur");
	  return (NULL);
  }
  if ((s = create_server_socket()) == -1) {
	  printf("error create server socket");
	  return (NULL);
  }
  srv->fd = s;
  srv->fd_max = s;
  printf("\nInitial server fd and fd_max: %d\n", s);
  srv->tick = &tick;
  srv->n_players = 0;
  srv->game_status = WAITING;

  game_info = calloc(1, sizeof(t_game_info));
  if (game_info == NULL) {
	  printf("error allocation memory game_info");
	  return (NULL);
  }
  set_game_info(game_info);

  for (i = 0; i < INLINE_MATRIX; ++i)
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
  // on set tout les player a 'non connecté'
  for (i = 0; i < 4; i++)
    {
      srv->players[i].connected = 0;
      srv->players[i].num_player = i;
      // mergé depuis la pr de kuma
      srv->players[i].fd = -1;
    }
  // on initialise le bench de request à NULL
  for (i = 0; i < 8; i++)
    srv->requests[i] = NULL;
  // on lance les 2 threads: la main loop du serveur et le ticker
  if (pthread_create(&tick_thread, NULL, threaded_ticker, &srv) != 0 )
  {
	  printf("error thread ticker");
	  return (NULL);
  }
  if (pthread_create(&main_thread, NULL, threaded_main_loop, &srv) != 0)
  {
	  printf("error thread main loop");
	  return (NULL);
  }
	pthread_join(tick_thread, NULL);
  pthread_join(main_thread, NULL);
  return (NULL);
}


int			create_server_socket()
{
  int s;
  struct sockaddr_in sin;
  int port;

  memset(&sin, 0, sizeof (struct sockaddr_in));
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
	  printf("error server socket init");
	  return (-1);
  }
  port = PORT;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
  {
	  printf("error socket binding\n");
	  return (-1);
  }
  if (listen(s, 42) == -1) {
	  printf("error serveur listening\n");
	  return (-1);
  }
  return (s);
}

// retourne 1 si il y a plus de 4 joueurs
int server_is_full(t_srv **srv)
{
	//DEV PURPOSE:
	fflush(stdout);
  if ((*srv)->n_players >= 4)
    return 1;
  return 0;
}

// défini si le serveur peut lancer la partie
int is_enought_players(t_srv **srv)
{
  if ((*srv)->n_players >= 2 && (*srv)->n_players < 5)
    return 1;
  return 0;
}

// set_fd_max définis le srv->fd_max par référence
void set_fd_max(t_srv **srv)
{
  int i;

  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
        {
          FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
          if ((*srv)->players[i].fd > (*srv)->fd_max)
            (*srv)->fd_max = (*srv)->players[i].fd;
        }
    }
}
