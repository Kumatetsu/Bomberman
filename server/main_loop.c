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
#include "request_serialization.h"
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

int main_loop(t_srv **srv)
{
  int i;
  int	error;
  socklen_t len;
  int retval;
  // int			response_type;
  struct timeval it_value;
  t_player_request player_request = {0};
  int survivors;
  i = 0;
  // On initialise direct la game_info
  // on utilise ensuite is_running() pour savoir si ca tourne
  // puis on récupère la static remplie
  FD_ZERO(&(*srv)->fd_read);
  FD_SET((*srv)->fd, &(*srv)->fd_read);

  // server.h définition du fd max pour le select, defaut dans init_server
  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
        {
	  FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);

	  if ((*srv)->players[i].fd > (*srv)->fd_max)
	    (*srv)->fd_max = (*srv)->players[i].fd;
        }
    }

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

  if (!server_is_full(srv))
    {
      // ici on accepte les connections clientes
      if (FD_ISSET((*srv)->fd, &(*srv)->fd_read) != 0)
        {
          // player.h
          if ((i = accept_players(srv)) == -1)
            return 0;
        }
    }

  if (is_enought_players(srv) && (*srv)->game_status != RUNNING)
    {
      // server.h
      // set le game_status à 1
      // copie les joueurs dans la game_info
      // passe le connected à 1 pour tous
      // définis le placement
      printf("\nStart Game\n");
      (*srv)->game_status = RUNNING;
      // start_game(srv);
      //
    }
  survivors = 0;
  // pour les joueurs... 0 à 3
  for (i = 0; i < 4; i++)
    {
      // Si le joueur est connecté... (c'est set à 1 dans server/create_game.c::create_game_info)
      if ((*srv)->players[i].connected == 1)
        {
	  len = sizeof(error);
	  // interroge les options de la socket (player->fd) pour détecter une erreur
	  // Si erreur on déco le player, ca évite de réitérer dessus
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
	  // Si la socket du player est set on traite...
	  if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read) != 0)
	    {
	      int n = 0;
	      // char buffer[sizeof(int)];
	      // ??? merge chelou
	      int buffer;
	      // char buffer[sizeof(t_game_info)];
	      printf("\nHandling request for player\n");
	      // On extrait le contenu
#ifdef _WIN32
	      n = recv((*srv)->players[i].fd, (char*)&buffer, sizeof(buffer), 0);
#else
	      n = recv((*srv)->players[i].fd, &buffer, sizeof(buffer), 0);
#endif
	      if (n > 0)
                {
		  if ((*srv)->game_status != RUNNING)
		    continue;

		  player_request.command = ntohl(buffer);
		  player_request.num_player = i;
		  printf("server: num player %d and command %d", player_request.num_player, player_request.command);
		  command_interpretor(srv, player_request);
		  // else
		  // {
		  //     printf("\nCLIENT REQUEST COMMAND: %d\n", player_request.command);
		  //     // handle_requests(game_info, &player_request);

		  //     // response_type = define_response_type(player_request.command);
		  //     response_pos.id = MOVE;
		  //     response_pos.x = 0;
		  //     response_pos.y = 0;

		  //     write((*srv)->players[i].fd, &response_pos, sizeof(response_pos));
		  // }
		}
	      else {
#ifdef _WIN32
		printf("recv from main_loop.c failed with error: %d\n", WSAGetLastError());
#else
		printf("recv from main_loop.c failed\n");
#endif
	      }
	      printf("client send request\n");
            }
        }
      if ((*srv)->players[i].alive && (*srv)->players[i].connected)
        {
	  survivors++;
        }
    }
  if ((*srv)->game_status == RUNNING && survivors <= 1)
    {
      (*srv)->game_status = ENDGAME;
      (*srv)->running = ENDGAME;
      reset_players(srv);
      (*srv)->game_status = RUNNING;
      (*srv)->running = RUNNING;
      for (i = 0; i < 4; i++)
	notify_actual_players(srv, 0);
    }
  return (1);
}
