/*
** request.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:06 2018 hochar_n
** Last update Thu Jul  5 21:38:07 2018 hochar_n
*/

#ifndef _REQUEST_H_
#define _REQUEST_H_

/*
 Je suis pour:
  - renommer request.h en network.h ou networking.h
*/
#include "system.h"
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct	s_player_request
{
  int		checksum;        /* Un checksum simple */
  unsigned int	magic;           /* Un magic number common entre le client et le serveur, ou l'identifiant d'un type de structure */
  int		y_pos;           /* La position y souhaitée par le client */
  int		x_pos;           /* La position x souhaitée par le client */
  int		dir;             /* La direction souhaitée par le client */
  int		command;         /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  int		num_player;      /* num_player between 0 and 3 */
}		t_player_request;

enum	CLIENT_REQUEST_STATUS
{
  BAD_SEND,
  SUCCESS_SEND,
  BAD_RECEIVE,
  SUCCESS_RECEIVE,
  BAD_FREE,
  SUCCESS_FREE
};

enum			COMMAND_REQUEST
{
    START_GAME=1,
    PLACE_BOMB=2
};

void			my_bzero(void *s1, int n);
int			send_request(int s, t_player_request *client_request);
int			get_msg(int s);
t_player_request* 	create_player_request();
int 			free_player_request(t_player_request* client_request);
char* 			request_serialization(t_player_request* client_request);
t_player_request* 	request_deserialize(char* serialized_request);
int			get_request_checksum(t_player_request* client_request);

#endif
