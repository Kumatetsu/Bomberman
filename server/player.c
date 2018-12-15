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
#include "socket.h"
#include "player_info.h"
#include "request.h"
#include "server.h"
#include "map.h"
#include "data.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"
#include "player.h"

// instanciation d'un player avec sa socket
int             add_player(t_srv **srv, int fd)
{
  t_player_info new_player;

  // très étrange, un new_player n'est pas malloc
  // du coup à la fin, players[(*srv)->n_players] = new_player
  // fait pointer sur un espace mémoire qui sera détruit
  // à la fin de l'appel de add_player non?
  new_player.connected = 1;
  new_player.alive = 1;
  new_player.dying = 0;
  new_player.x = 0;
  new_player.y = 0;
  new_player.current_dir = 0;
  new_player.bomb_left = 1;
  new_player.fd = fd; 
  // index entre 0 et 3 pour indexation array                                        
  new_player.num_player = (*srv)->n_players;
  /**
   ** IL MANQUE SDL_Rect bomber_sprites[5][4]; à instancier dans le t_player
   */
  (*srv)->players[(*srv)->n_players] = new_player;
  (*srv)->n_players++;
  printf("player added");
  return (1);
}

// accepte la connection
// add le player (instanciation)
// vérifie qu'on est bon niveau mallocage
// retourne l'index
int			accept_players(t_srv **srv)
{
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
