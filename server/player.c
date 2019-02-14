/*
** player.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:39:00 2018 MASERA Mathieu
** Last update Wed Jul  4 09:39:01 2018 MASERA Mathieu
*/


#include "system.h"
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

void		reset_players(t_srv **srv)
{
  t_player_info	p;
  
  for (int i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected && (*srv)->players[i].fd != -1) {
	fflush(stdout);
	p = (*srv)->players[i];
	p.alive = 1;
	p.dying = 0;
	p.action_sprite = not_move;
	p.bomb_left = 3;
	define_player_init_pos(&(p));
	(*srv)->players[i] = p;
	printf("PLAYER RESET: id: %d alive:%d action:%d move%d\n", i, p.alive, p.action_sprite, p.direction_sprite);
      }
    }
}

//instanciation of a player with it socket
int		add_player(t_srv **srv, int fd)
{
  t_player_info new_player;

  new_player.connected = 1;
  // index between 0 and 3 for array indexation of players
  new_player.num_player = (*srv)->n_players;
  new_player.alive = 1;
  new_player.dying = 0;
  new_player.direction_sprite = bomber_d;
  new_player.action_sprite = not_move;
  new_player.bomb_left = 1;
  new_player.fd = fd;
  define_player_init_pos(&new_player);
  (*srv)->players[(*srv)->n_players] = new_player;
  (*srv)->n_players++;
  printf("player added number %d\n\n", (*srv)->n_players);
  return (1);
}

// accept the connection
// add the player (instanciation)
// check we have a correct memory allocation
// return the index
int			accept_players(t_srv **srv)
{
  int		        index;
  int			player_socket;
  SOCKADDR_IN		client_sin;
  socklen_t		client_sin_len;

  index = (*srv)->n_players;
  printf("\naccept_player, index: %d\n", index);
  memset(&client_sin, 0, sizeof (SOCKADDR_IN));
  client_sin_len = sizeof (client_sin);
  printf("before accept player accept()\n");
  player_socket = accept((*srv)->fd, (SOCKADDR *)&client_sin, &client_sin_len);
  printf("\naccept_player, player_socket: %d\n", player_socket);
  if (player_socket == -1) {
#ifdef _WIN32
    printf("accept player_socket failed with error %d\n", WSAGetLastError());
#endif
    return (-1);
  }
  if (!add_player(srv, player_socket)) {
    return (-1);
  }
  return (index);
}

void define_player_init_pos(t_player_info *player)
{
  /*
   * a bloc is  48px
   * ordonate: 13 blocks
   * abscix: 15 blocks
   * by default we place a player in the middle of a block
   * example with the player 1 placement : 48 + 24 = 72 for the bloc x = y = 2
   */
  switch (player->num_player)
    {
    case 0:
      player->x = (I_BEGIN + 1) * 48;        // = 200px
      player->y = ((J_BEGIN + 1) * 48) - 36; // = 156 px
      player->current_dir = BOMBER_L;
      break;
    case 1:
      player->x = (I_BEGIN + 13) * 48;        // = 776px
      player->y = ((J_BEGIN + 11) * 48) - 36; // = 636px
      player->current_dir = BOMBER_D;
      break;
    case 2:
      player->x = (I_BEGIN + 1) * 48;         // = 200px
      player->y = ((J_BEGIN + 11) * 48) - 36; // = 636px
      player->current_dir = BOMBER_U;
      break;
    case 3:
      player->x = (I_BEGIN + 13) * 48;       // = 776px
      player->y = ((J_BEGIN + 1) * 48) - 36; // = 156px
      player->current_dir = BOMBER_R;
      break;
    }
}
