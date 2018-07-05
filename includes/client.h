/*
** client.h for Project-Master in /home/enach/CLionProjects/Bomberman
** 
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
** 
** Started on  Thu Jul  5 21:37:33 2018 hochar_n
** Last update Thu Jul  5 21:37:35 2018 hochar_n
*/

#ifndef _CLIENT_H_
#define _CLIEN_H_

#include "request.h"
#include "sdl.h"

void 	client_loop(t_sdl *sdl, int fd, t_player_request *cr);
void	init_client(t_sdl *sdl);
char	*enter_addr(t_sdl *sdl);
int	host_connect();
int	client_connect();
int	get_message(int s);
#endif
