/*
** socket.c<2> for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
** 
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
** 
** Started on  Tue Jun 26 17:52:39 2018 BILLAUD Jean
** Last update Tue Jul  3 23:42:48 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>
#include <pthread.h>
#include "bomberman.h"
#include "sdl.h"
#include "client.h"
#include "player_info.h"
#include "server.h"
#include "thread.h"
#include <errno.h>

//init de la socket client + connection à une socket server.
int	host_connect()
{
  struct protoent	*pe;
  struct sockaddr_in	sin ;
  int	s;
  int port;

  memset(&sin, 0, sizeof(struct sockaddr_in));
  port = PORT;
  pe = getprotobyname("TCP");
  if (pe == NULL)
    return (-1);
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  if(connect(s, (const struct sockaddr *)&sin, sizeof (sin)) == -1)
    {
      printf("error connection\n");
      exit(errno);
    }
  printf("connected\n");
  return (s);
}

int	client_connect(char *serv_addr)
{
  struct protoent	*pe;
  struct sockaddr_in	sin ;
  int	s;
  int port;

  memset(&sin, 0, sizeof(struct sockaddr_in));
  port = PORT;
  pe = getprotobyname("TCP");
  if (pe == NULL)
    {
      printf("error protocole for socket client");
      return (-1);
    }
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    {
      printf("error socket client");
      return (-1);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(serv_addr);
  if(connect(s, (const struct sockaddr *)&sin, sizeof (sin)) == -1)
    {
      printf("error connection\n");
      exit(errno);
    }
  printf("connected\n");
  return (s);
}
