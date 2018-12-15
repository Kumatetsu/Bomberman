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
#include "player_info.h"
#include "server.h"
#include "request.h"
#include "game_info.h"
#include "my_put.h"
#include "main_loop.h"

int main_loop(t_srv **srv)
{
  int i;
  int error;
  socklen_t len;
  int retval;
  t_player_request *player_request;
  t_game_info *game_info;
  int num_player;
  char		log[50];

  printf("\n\nMain_loop entry\n");
  i = 0;
  // On initialise direct la game_info
  // on utilise ensuite is_running() pour savoir si ca tourne
  create_game_info(srv);
  // puis on récupère la static remplie
  game_info = get_game_info();
  
  printf("\nFDZERO\n");
  FD_ZERO(&(*srv)->fd_read);
  printf("\nFDSET\n");
  FD_SET((*srv)->fd, &(*srv)->fd_read);
  // server.h définition du fd max pour le select, defaut dans init_server
  printf("\nset_fd_max\n");
  printf("\nfd max before: %d\n", (*srv)->fd_max);
  for (i = 0; i < 4; i++)
    {
      printf("\nplayer connected = %d\n", (*srv)->players[i].connected);
      printf("\nfd player = %d\n", (*srv)->players[i].fd);
      if ((*srv)->players[i].connected == 1)
			{
				FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
				printf("\nfd player = %d\n", (*srv)->players[i].fd);
				if ((*srv)->players[i].fd > (*srv)->fd_max)
					{ 
						(*srv)->fd_max = (*srv)->players[i].fd;
						printf("\nfd_max = %d\n", (*srv)->fd_max);
					}
			}
  
			// set_fd_max(srv);
			printf("\nfd_max after: %d\n", (*srv)->fd_max);
			
			// select sur la socket server
			printf("\nselect\n");
			if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
				return (0);
			// server.h
			// on accepte des joueurs, si y'a la place et si y'a requete
			if (!server_is_full(srv))
				{
					error = 0;
					len = sizeof(error);
					retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, &error, &len);
					if (retval != 0 || error != 0)
					{
						(*srv)->players[i].connected = 0;
						continue;
					}
					if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read))
					{
						int n = 0;

						char buffer[sizeof(t_game_info)];
						n = recv((*srv)->players[i].fd, buffer, sizeof(t_game_info), 0);
						printf("serv: client fd: %d with n:%d\n\n", (*srv)->players[i].fd, n);
						if (n > 0)
						{
							sprintf(log, "in client sent request\n\n\n\n\n");
							my_putstr(log);
							player_request = (t_player_request*)(buffer);
							num_player = (*srv)->players[i].num_player;
							handle_requests(game_info, player_request);
							sprintf(log, "%d\n\n\n\n\n\n", game_info->players[num_player - 1].y_pos);
							my_putstr(log);
							my_putstr("GET REQUEST DUMB DUMB\n\n\n\n\n");
							// if (player_request->checksum != get_request_checksum(player_request))
							// {
							//   close((*srv)->players[i].fd);
							//   (*srv)->players[i].connected = 0;
							// }
							// n = 0;
						}
						buffer[n] = 0;
						printf("client sent request\n");
					}
				}
			if ((!is_running() && is_enought_players(srv))
					// FOR DEV
					|| (*srv)->n_players
					)
				{
					// server.h
					// set le game_status à 1
					// copie les joueurs dans la game_info
					// passe le connected à 1 pour tous
					// définis le placement
					printf("\nStart Game\n");
					start_game(srv);
					//
				}
			if (is_running()
					// FOR DEV
					|| (*srv)->n_players)
				{
		
					printf("\nITERATE THROUGHT PLAYERS\n");
					// pour les joueurs... 
					for (i = 0; i < 4; i++)
			{
				// Si le joueur est connecté... (c'est set à 1 dans server/create_game.c::create_game_info)
						printf("\nPlayer %d connected?\n", i);
				if ((*srv)->players[i].connected == 1)
					{
						printf("\nYes\n");
						error = 0;
						len = sizeof (error);
						// interroge les options de la socket (player->fd) pour détecter une erreur
						retval = getsockopt ((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, &error, &len);
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
						if((n = recv((*srv)->players[i].fd, buffer, sizeof(t_game_info), 0)) < 0)
										{
					perror("recv()");
					player_request = request_deserialize(buffer);
					num_player  = (*srv)->players[i].num_player;
					handle_requests(game_info, player_request);
					printf("%s", request_serialization(player_request));
					my_putstr("GET REQUEST DUMB DUMB\n\n\n\n\n");
					if (player_request->checksum != get_request_checksum(player_request))
						{
							// on désérialize
							player_request = request_deserialize(buffer);
							printf("\nGAMEINFO tick nb: %d\n", game_info->tick_time);
							// on modifie la game_info
							handle_requests(game_info, player_request);
							// printf("\nPLAYER REQUEST: %s\n", request_serialization(player_request));
							// On assure au serveur l'origine de la requête
							if (player_request->checksum != get_request_checksum(player_request))
					{
						close((*srv)->players[i].fd);
						(*srv)->players[i].connected = 0;
					}
							n = 0;
						}
					buffer[n] = 0;
					printf("client send request\n");
				}
					}
				else
					printf("\nnot connected\n");
			}
    }
	}
		
  // à réviser le process request
  // process_requests(srv);
  return (1);
}
}
