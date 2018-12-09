/*
** request_serialization.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/common
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:34:41 2018 MASERA Mathieu
** Last update Wed Jul  4 09:34:42 2018 MASERA Mathieu
*/

#include <stdio.h>
#include "request.h"

int	get_request_checksum(t_player_request* client_request)
{
  int	checksum = 0;
  int	i;

  unsigned char *p = (unsigned char *)&client_request->magic;
  for (i = 0; i<(int)sizeof(client_request->magic); i++) {
    checksum += p[i];
  }
  p = (unsigned char *)&client_request->command;
  for (i = 0; i<(int)sizeof(client_request->command); i++)
    checksum += p[i];
  p = (unsigned char *)&client_request->num_player;
  for (i = 0; i<(int)sizeof(client_request->num_player); i++)
    checksum += p[i];
  return checksum;
}

char*	request_serialization(t_player_request* client_request)
{
  char*	request_string;

  printf("\nBefore calloc\n");
  request_string = calloc(1, sizeof(t_player_request));
  printf("\nAfter calloc\n");
  if (request_string == NULL)
    return NULL;
  client_request->checksum = get_request_checksum(client_request);
  request_string = (char*) client_request;
  printf("\nBefore realloc\n");
  request_string = realloc(request_string,sizeof(t_player_request)+1);
  printf("\nAfter realloc\n");
  if (request_string == NULL)
    return NULL;
  request_string[sizeof(t_player_request)] = '\0';
  return request_string;
}

t_player_request*	request_deserialize(char* request_serialized)
{
  t_player_request*	client_request;

  client_request = (t_player_request*)request_serialized;
  return client_request;
}
