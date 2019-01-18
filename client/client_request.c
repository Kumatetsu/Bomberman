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

int			send_request(int s, int command)
{
  int tmp;

  tmp = htonl(command);
  write(s, &tmp, sizeof(tmp));
  return SUCCESS_SEND;
}
