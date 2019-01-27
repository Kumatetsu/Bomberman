/*
** main_loop.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:37:32 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:33 2018 MASERA Mathieu
*/

#include <stdio.h>
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
#include "request_handling.h"
#include "main_loop.h"
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <time.h>

void		restart_game(t_srv **srv)
{
  t_game_info	*game_info;

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
  int			i;
  int			error;
  socklen_t		len;
  int			retval;
  t_player_request	*player_request;
  t_game_info		*game_info;
  int			survivors;
  
  printf("\nMAIN_LOOP\n");
  i = 0;
  // On initialise direct la game_info
  // on utilise ensuite is_running() pour savoir si ca tourne
  if (NULL == get_game_info())
    create_game_info();
  // puis on récupère la static remplie
  game_info = get_game_info();
  FD_ZERO(&(*srv)->fd_read);
#ifdef _WIN32
  FD_SET((unsigned int)(*srv)->fd, &(*srv)->fd_read);
#else
  FD_SET((*srv)->fd, &(*srv)->fd_read);
#endif
  // server.h définition du fd max pour le select, defaut dans init_server
  for (i = 0; i < 4; i++)
    {
      if ((*srv)->players[i].connected == 1)
	{
#ifdef _WIN32
	  FD_SET((unsigned int)(*srv)->players[i].fd, &(*srv)->fd_read);
#else
	  FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
#endif
	  if ((*srv)->players[i].fd > (*srv)->fd_max)
	    (*srv)->fd_max = (*srv)->players[i].fd;
	}
    }
  printf("\nselect\n");

  if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
  {
	  printf("error select main loop\n");
	  return (0);
  }

  if (!server_is_full(srv))
    {
      // ici on accepte les connections clientes
      if (FD_ISSET((unsigned int)(*srv)->fd, &(*srv)->fd_read))
		{
	  // player.h
		  if ((i = accept_players(srv)) == -1)
			{	
			  printf("error accept_players server from main loop");
			  return 0;
			}
	  // on a bougé les players du srv, on refresh ceux de la game_info
	  game_info->players[i] = (*srv)->players[i];
	  game_info->nb_client = (*srv)->n_players;
		}
    }
  // FOR PROD
  //if (!is_running() && is_enought_players(srv))
  // FOR DEV
  if (is_enought_players(srv) && !is_running())
    {
	  printf("hello there");
      // server.h
      // set le game_status à 1
      // copie les joueurs dans la game_info
      // passe le connected à 1 pour tous
      // définis le placement
      printf("\nStart Game\n");
      start_game(srv);
      //
    }
  if (is_running())
    {
      survivors = 0;

      // pour les joueurs... 0 à 3
      for (i = 0; i < 4; i++)
	{
	  // Si le joueur est connecté... (c'est set à 1 dans server/create_game.c::create_game_info)
	  if ((*srv)->players[i].connected == 1)
	    {
	      printf("\nPlayer %d command\n", i);
	      error = 0;
	      len = sizeof (error);
	      // interroge les options de la socket (player->fd) pour détecter une erreur
#ifdef _WIN32
	      retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, "error", &len);
#else
		  retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, (char*)error, &len);
#endif
		  // Si erreur on déco le player, ca évite de réitérer dessus
	      if (retval != 0 || error != 0) {
			(*srv)->players[i].connected = 0;
			continue;
	      }
	      // Si la socket du player est set on traite...
	      if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read))
		{
		  int n = 0;
		  char buffer[sizeof(t_game_info)];
		  printf("\nHandling request for player %d\n", i);
		  // On extrait le contenu
		  if((n = recv((*srv)->players[i].fd, buffer, sizeof(t_game_info), 0)) > 0)
		    {
		      // on désérialize
		      player_request = request_deserialize(buffer);
		      player_request->num_player = i;
		      printf("\nGAMEINFO tick nb: %d\n", game_info->tick_time);
		      printf("\nCLIENT REQUEST COMMAND: %d\n", player_request->command);
		      // on modifie la game_info
		      handle_requests(game_info, player_request);
		      // printf("\nPLAYER REQUEST: %s\n", request_serialization(player_request));
		      // On assure au serveur l'origine de la requête
		      /* if (player_request->checksum != get_request_checksum(player_request))
			 {
			 close((*srv)->players[i].fd);
			 (*srv)->players[i].connected = 0;
			 }*/
		      n = 0;
		    }
		  buffer[n] = 0;
		  printf("client send request\n");
		}
	    }
	  if (game_info->players[i].alive)
	    survivors++;
	}
      if (survivors <= 1)
	{
	  
	  game_info->game_status = ENDGAME;
	  (*srv)->running = ENDGAME;
	  printf("\nENDGAME\n");
	  restart_game(srv);
	}
    }
  printf("\nGAME STATUS: %d\n", game_info->game_status);
  return (1);
}
