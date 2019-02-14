/*
** thread.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:15 2018 hochar_n
** Last update Thu Jul  5 21:38:17 2018 hochar_n
*/

#ifndef _THREAD_H_
#define _THREAD_H_
#include "data.h"

typedef struct	s_thread
{
  int		socket;
  t_data	*data;
} t_thread;

typedef struct	s_bomb_thread
{
  t_srv		**srv;
  int		index;
} t_bomb_thread;

void *thread_listen_serv(void *s_info);
void *server_thread(void *s_info);
//void *threaded_ticker(void *tick);
void *threaded_main_loop(void *server);
void *bomb_thread_func(void *bomb_thread_struct);

#endif /* !_THREAD_H_ */
