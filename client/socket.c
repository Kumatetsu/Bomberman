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

int	my_connect()
{
  struct protoent	*pe;
  struct sockaddr_in	sin = { 0 };
  int	s;


  pe = getprotobyname("TCP");
  if (pe == NULL)
    return (-1);
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(666);
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  if(connect(s, (const struct sockaddr *)&sin, sizeof (sin)) == -1)
    {
      printf("error connection\n");
    }
  return (s);
}
