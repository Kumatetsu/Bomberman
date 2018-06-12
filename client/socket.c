#include <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "sdl.h"
#include "client.h"
#include "server.h"
#include "thread.h"
#include <errno.h>

//init de la socket client + connection à une socket server.
int	my_connect()
{
  struct protoent	*pe;
  struct sockaddr_in	sin ;
  int	s;
  int port;

  memset(&sin, 0, sizeof(struct sockaddr_in));
  port = 4022;
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
