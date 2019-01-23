/*
** networking.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:39:00 2018 MASERA Mathieu
** Last update Wed Jul  4 09:39:01 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "data.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"
#include "player.h"
#include "constant.h"
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#ifdef linux
typedef int SOCKET;
typedef struct sockaddr_in client_sin;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct socklen_t client_sin_len;
#endif

// instanciation d'un player avec sa socket
int             add_player(t_srv **srv, int fd)
{
  t_player_info new_player;

  // très étrange, un new_player n'est pas malloc
  // du coup à la fin, players[(*srv)->n_players] = new_player
  // fait pointer sur un espace mémoire qui sera détruit
  // à la fin de l'appel de add_player non?
  new_player.connected = 1;
  // index entre 0 et 3 pour indexation array
  new_player.num_player = (*srv)->n_players;
  new_player.alive = 1;
  new_player.dying = 0;
  new_player.direction_sprite = bomber_d;
  new_player.action_sprite = not_move;
  new_player.bomb_left = 1;
  new_player.fd = fd;
  define_player_init_pos(&new_player);

  /**
   ** IL MANQUE SDL_Rect bomber_sprites[5][4]; à instancier dans le t_player
   */
  (*srv)->players[(*srv)->n_players] = new_player;
  (*srv)->n_players++;
  printf("player added number %d\n\n", (*srv)->n_players);
  return (1);
}

// accepte la connection
// add le player (instanciation)
// vérifie qu'on est bon niveau mallocage
// retourne l'index
int			accept_players(t_srv **srv)
{

#ifdef _WIN32
	WORD versionWanted = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(versionWanted, &wsaData);
#endif

  int		        index;
  int			player_socket;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  index = (*srv)->n_players;
  printf("\naccept_player, index: %d\n", index);
  memset(&client_sin, 0, sizeof (struct sockaddr_in));
  client_sin_len = sizeof (client_sin);
  player_socket = accept((*srv)->fd, (struct sockaddr *)&client_sin, &client_sin_len);
  printf("\naccept_player, player_socket: %d\n", player_socket);
  if (player_socket == -1)
    return (-1);
  if (!add_player(srv, player_socket))
    return (-1);
  if (index == ((*srv)->n_players) - 1)
    my_putstr("\nPlayer successfully added");
  else if ((*srv)->players[index].bomb_left == 1)
    // Check l'affectation mémoire immédiatement
    printf("\nPlayer have %d bomb.\n", (*srv)->players[index].bomb_left);
  else
    my_putstr("\nServer failed to add client");
  // retourne 1 si joueur ajouté, 0 sinon
  return (index);
}


void define_player_init_pos(t_player_info *player)
{
  /*
  * un bloc fait 48px
  * ordonnée: 13 blocks
  * abscice: 15 blocks
  * par défaut on place un joueur au milieux d'un case
  * exemple placement joueur 1 : 48 + 24 = 72 pour la case x = y = 2
  */
  switch (player->num_player)
    {
    case 0:
      player->x = (I_BEGIN + 1) * 48; // = 200px
      player->y = ((J_BEGIN + 1) * 48) - 36; // = 156 px
      player->current_dir = BOMBER_L;
      break;
    case 1:
      player->x = (I_BEGIN + 13) * 48; // = 776px
      player->y = ((J_BEGIN + 11) * 48) - 36; // = 636px
      player->current_dir = BOMBER_D;
      break;
    case 2:
      player->x = (I_BEGIN + 1) * 48; // = 200px
      player->y = ((J_BEGIN + 11) * 48) - 36; // = 636px
      player->current_dir = BOMBER_U;
      break;
    case 3:
      player->x = (I_BEGIN + 13) * 48; // = 776px
      player->y = ((J_BEGIN + 1) * 48) - 36; // = 156px
      player->current_dir = BOMBER_R;
      break;
    }
}
