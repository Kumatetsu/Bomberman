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

t_player_request*       create_player_request()
{
  t_player_request*	client_request;

  srand(time(NULL));
  client_request = calloc(1, sizeof(t_player_request));
  if (client_request == NULL)
    return NULL;
  return client_request;
}

int free_player_request(t_player_request* client_request)
{
  free(client_request);
  if (client_request == NULL)
    return SUCCESS_FREE;
  return BAD_FREE;
}

int			send_request(int s, t_player_request* client_request)
{
  t_player_request	dumb_static;
  memcpy(&dumb_static.checksum, &client_request->checksum, sizeof(int));
  memcpy(&dumb_static.command, &client_request->command, sizeof(int));
  write(s, &dumb_static, sizeof(t_player_request));
  return SUCCESS_SEND;
}
