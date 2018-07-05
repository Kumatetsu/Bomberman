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
  unsigned int		magic;

  srand(time(NULL));
  magic = (rand() % INT_MAX);
  client_request = calloc(1, sizeof(t_player_request));
  if (client_request == NULL)
    return NULL;
  client_request->magic = magic;
  client_request->checksum = get_request_checksum(client_request);
  return client_request;
}

int free_player_request(t_player_request* client_request)
{
  free(client_request);
  if (client_request == NULL)
    return SUCCESS_FREE;
  return BAD_FREE;
}

int         send_request(int s, t_player_request* client_request)
{
  char*     request_string;

  request_string = request_serialization(client_request);
  if (strlen(request_string) > 0)
    {
      printf("SEND REQUEST\n");
      write(s, request_string, strlen(request_string));
      return SUCCESS_SEND;
    }
  else
    {
      write(1, "exit\n", 5);
      return BAD_SEND;
    }
}

int		get_msg(int s)
{
  char		buff[1024];
  int		r;

  my_bzero(buff, 1024);
  r = recv(s, buff, 1024, 0);
  if (r > 0)
    {
      buff[r] = '\0';
      write(1, buff, r);
      return SUCCESS_RECEIVE;
    }
  else
    {
      write(1, "Connection closed\n", 18);
      return BAD_RECEIVE;
    }
}
