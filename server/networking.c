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
#include "sdl.h"
#include "player.h"
#include "socket.h"
#include "thread.h"
#include "request.h"
#include "game_info.h"
#include "my_put.h"
#include "server.h"

int			accept_players(t_srv **srv)
{
  int			check;
  int			player_socket;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  t_game_info   *game_info;

  check = (*srv)->n_players;
  memset(&client_sin, 0, sizeof (struct sockaddr_in));
  client_sin_len = sizeof (client_sin);
  player_socket = accept((*srv)->fd, (struct sockaddr *)&client_sin, &client_sin_len);
  if (player_socket == -1)
    return (-1);
  if ((*srv)->n_players >= 4)
    return (0);
  if (!add_player(srv, player_socket))
    return (-1);
  if (check == ((*srv)->n_players) - 1)
    my_putstr("\nPlayer successfully added");
  else
    my_putstr("\nServer failed to add client");
  // retourne 1 si joueur ajouté, 0 sinon
  if ((*srv)->n_players == 1 && ((*srv)->n_players - check) == 1)
  {
    my_putstr("\nCreation of the game");
    create_game_info(srv);
    my_putstr("\nGame created");
  } else if ((*srv)->n_players > 2 && check > 0)
  {
    game_info = get_game_info();
    game_info->players[check-1] = (*srv)->players[check-1];
    set_game_info(game_info);
  }
  return ((*srv)->n_players - check);
}
