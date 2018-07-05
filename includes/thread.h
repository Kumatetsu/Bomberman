#ifndef _THREAD_H_
#define _THREAD_H_
#include "sdl.h"
#include "client.h"
#include "player_info.h"
#include "player.h"
#include "base_map.h"

typedef struct		s_thread
{
  int			socket;
  t_data       *data;
}			t_thread;

void *thread_listen_serv(void *s_info);
void *server_thread(void *s_info);
void *threaded_ticker(void *tick);
void *threaded_main_loop(void *server);

#endif /* !_THREAD_H_ */
