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

#ifdef _WIN32
#include <winsock2.h>
#endif

#ifdef linux
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "enum.h"
#include <time.h>

typedef struct s_player_request
{
  int y;                        /* La position y souhaitée par le client */
  int x;                        /* La position x souhaitée par le client */
  int dir;                      /* La direction souhaitée par le client */
  enum COMMAND_REQUEST command; /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  int num_player;               /* num_player between 0 and 3 */
} t_player_request;

typedef struct s_server_response
{
  int response_type;
  void *content;
} t_server_reponse;

void my_bzero(void *s1, int n);
int send_request(int s, int command);

#endif /* !_CLIENT_REQUEST_H_ */
