/*
** main_loop.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:37:32 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:33 2018 MASERA Mathieu
*/

#include "system.h"
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "player_info.h"
#include "server.h"
#include "player.h"
#include "map.h"
#include "game_info.h"
#include "my_put.h"
#include "main_loop.h"
#include "response_type_utils.h"
#include "server_request.h"
#include "notify_client.h"
#include "command_interpretor.h"

void restart_game(t_srv **srv)
{
  t_game_info *game_info;

  game_info = get_game_info();
  reset_players(srv);
  for (int i = 0; i < 4; i++)
    {
      game_info->players[i] = (*srv)->players[i];
    }
  game_info->game_status = 1;
  (*srv)->running = 1;
}

int			main_loop(t_srv **srv)
{
  int			i, n;
  int			error;
  socklen_t		len;
  int			retval;
  struct timeval	it_value;
  t_player_request	player_request = {0};
  int			survivors;

  i = 0;
  // We use directly the game info
  // We use then the is_running() to know if it runs
  // then we get the filled static
  FD_ZERO(&(*srv)->fd_read);
  FD_SET((*srv)->fd, &(*srv)->fd_read);

  // server.h definition of the fd_max for the select, default in init_server
  set_fd_max(srv);

  it_value.tv_sec = 0;
  it_value.tv_usec = 100000;
  if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, &it_value) == -1) {
#ifdef _WIN32
    printf("select error: %d\n", WSAGetLastError());
#else
    printf("select error main_loop\n");
#endif
    return (0);
  }

  if (!server_is_full(srv)) {
    //we accept client connections
    if (FD_ISSET((*srv)->fd, &(*srv)->fd_read) != 0) {
      // player.h
      if ((i = accept_players(srv)) == -1)
	return 0;
    }
  }

  if (is_enought_players(srv) && (*srv)->game_status != RUNNING)
    {
      // server.h
      // set the game_status to 1
      // copy players in the game_info
      // put connected status to every players
      // define placement
      printf("\nStart Game\n");
      (*srv)->game_status = RUNNING;
      // start_game(srv);
    }
  survivors = 0;
  // for the players 1 to 4 
  for (i = 0; i < 4; i++)
    {
      // If the player is connected (it's set to 1 in server/create_game::create_game_info
      if ((*srv)->players[i].connected == 1) {
	len = sizeof(error);
	// asks if the sockets options (player->fd) contains errors
	// if errors, we disconnect the players so we don't iterate on it anymore
#ifdef _WIN32
	retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
	if (retval != 0) {
	  printf("error getsockopt main_loop: WSACode: %d, error getsockopt: %d\n", WSAGetLastError(), error);
	  (*srv)->players[i].connected = 0;
	  continue;
	}
#else
	error = 0;
	retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, &error, &len);
	if (retval != 0 || error != 0) {
	  printf("error getsockopt main_loop: %d\n", error);
	  (*srv)->players[i].connected = 0;
	  continue;
	}
#endif
	// If the player socket is set we then try to receive from it
	if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read) != 0) {
	  n = 0;
	  int buffer;
	  printf("\nHandling request for player\n");
	  // 
#ifdef _WIN32
	  n = recv((*srv)->players[i].fd, (char*)&buffer, sizeof(buffer), 0);
#else
	  n = recv((*srv)->players[i].fd, &buffer, sizeof(buffer), 0);
#endif
	  if (n > 0) {
	    if ((*srv)->game_status != RUNNING) {
	      continue;
	    }
	    player_request.command = ntohl(buffer);
	    player_request.num_player = i;
	    printf("server: num player %d and command %d", player_request.num_player, player_request.command);
	    command_interpretor(srv, player_request);
	  } else {
#ifdef _WIN32
	    printf("recv from main_loop.c failed with error: %d\n", WSAGetLastError());
#else
	    printf("recv from main_loop.c failed\n");
#endif
	  }
	  printf("client send request\n");
	}
      }
      if ((*srv)->players[i].alive && (*srv)->players[i].connected) {
	survivors++;
      }
    }
  if ((*srv)->game_status == RUNNING && survivors <= 1) {
    (*srv)->game_status = ENDGAME;
    (*srv)->running = ENDGAME;
    reset_players(srv);
    (*srv)->game_status = RUNNING;
    (*srv)->running = RUNNING;
    for (i = 0; i < 4; i++) {
      notify_actual_players(srv, 0);
    }
  }
  return (1);
}
