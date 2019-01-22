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
#define _CLIENT_H_

void	init_client(t_sdl *sdl);
char	*enter_addr(t_sdl *sdl);
int	client_connect(char *serv_addr);

#endif /* !_CLIENT_H_ */
