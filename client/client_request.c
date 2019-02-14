/*
** client_request.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Fri Jun 29 16:23:26 2018 BILLAUD Jean
** Last update Sat Jun 30 16:09:05 2018 MASERA Mathieu
*/

#include "sdl.h"
#include "enum.h"
#include "client_request.h"
#include "client.h"
#include "system.h"

void	my_bzero(void *s1, int n)
{
  char	*c;

  c = (char *)s1;
  while (n > 0)
    {
      *c++ = 0;
      n--;
    }
}

int	send_request(SOCKET s, int command)
{
  int	tmp;

  printf("command: %d", command);
  tmp = htonl(command);

#ifdef _WIN32
  int	nbrBytes = 0;
  if ((nbrBytes = send(s , (void*)&tmp, sizeof(tmp), 0)) < 0) {
    printf("error %d sending from send_request to server socket: %d \n", WSAGetLastError(), s);
  } else {
    printf("send_request to server from socket: %d  : %d bytes \n ", s, nbrBytes);
  }
#else
  write(s, &tmp, sizeof(tmp));
#endif

  return (SUCCESS_SEND);
}
