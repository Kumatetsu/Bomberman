/*
** request.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:06 2018 hochar_n
** Last update Thu Jul  5 21:38:07 2018 hochar_n
*/

#ifndef _CLIENT_REQUEST_H_
#define _CLIENT_REQUEST_H_

#include "system.h"
#include <limits.h>
#include <string.h>
#include "enum.h"
#include <time.h>

typedef struct		s_player_request
{
  int			y;          /* Position Y expected by the client */
  int			x;          /* Position X expected by the client */
  int			dir;        /* Direction exepected by the client */
  enum COMMAND_REQUEST	command;    /* A command from the client (0 : do nothing / 1 : put a bomb) */
  int			num_player; /* num_player between 0 and 3 */
} t_player_request;

typedef struct	s_server_response
{
  int		response_type;
  void		*content;
} t_server_reponse;

void	my_bzero(void *s1, int n);
int	send_request(SOCKET s, int command);

#endif /* !_CLIENT_REQUEST_H_ */
