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
#include "main_loop.h"
#include "my_put.h"

int			main_loop(t_srv **srv)
{
  int			i;
  int			error;
  socklen_t		len;
  int			retval;
  t_player_request	*player_request;
  t_game_info		*game_info;

  i = 0;
  // récupération du singleton game_info
  game_info = get_game_info();
  FD_ZERO(&(*srv)->fd_read);
  (*srv)->fd_max = (*srv)->fd;
  FD_SET((*srv)->fd, &(*srv)->fd_read);
  printf("\n\nMain_loop entry\n");
  // définition du fd max pour le select: le file descriptor le plus élevé
  while (i < 4 && (*srv)->players[i].connected == 1)
    {
      FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
      if ((*srv)->players[i].fd > (*srv)->fd_max)
	(*srv)->fd_max = (*srv)->players[i].fd;
      i++;
    }
  // select sur la socket server
  if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, NULL) == -1)
    return (0);
  // ici on accepte les connections clientes
  // on gère aussi l'activation du game, le paramètre connected des players etc...
  // trop de choses ici
  
  if (FD_ISSET((*srv)->fd, &(*srv)->fd_read)){
    // PBM: est appellé à tout les coups, même à jeux plein
    // server/networking.c::accept_player()
    // - accept la socket
    // - check si il reste de la place
    // - si oui et au moins 2 joueurs => create_game_info
    // retourne le nombre de places disponibles
    if (accept_players(srv) == -1)
      return 0;
  }
  // pour les joueurs... 
  for (i = 0; i < 4; i++)
    {
      // Si le joueur est connecté... (c'est set à 1 dans server/create_game.c::create_game_info)
      if ((*srv)->players[i].connected == 1)
       {
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

	      // On extrait le contenu
	      if((n = recv((*srv)->players[i].fd, buffer, sizeof(t_game_info), 0)) < 0)
                {
		  // on désérialize
		  player_request = request_deserialize(buffer);
		  // on modifie la game_info
		  handle_requests(game_info, player_request);
		  printf("\nPLAYER REQUEST: %s\n", request_serialization(player_request));
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
    }
  // à réviser le process request
  // process_requests(srv);
  return (1);
}
