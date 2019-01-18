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
#include <stdlib.h>
#include "client_request.h"
#include "request_serialization.h"

char*	request_serialization(t_player_request* client_request)
{
  char*	request_string;

  printf("\nBefore calloc\n");
  request_string = calloc(1, sizeof(t_player_request));
  printf("\nAfter calloc\n");
  if (request_string == NULL)
    return NULL;
  request_string = (char*) client_request;
  printf("\nBefore realloc\n");
  request_string = realloc(request_string,sizeof(t_player_request)+1);
  printf("\nAfter realloc\n");
  if (request_string == NULL)
    return NULL;
  request_string[sizeof(t_player_request)] = '\0';
  return request_string;
}

int	request_deserialize(char* request_serialized)
{
  int	command;

  command = atoi(request_serialized);
  return command;
}
