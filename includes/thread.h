#ifndef _THREAD_H_
#define _THREAD_H_

void *thread_listen_serv(void *s_info);
void *server_thread(void *s_info);
void *threaded_ticker(void *tick);
void *threaded_main_loop(void *server);

#endif /* !_THREAD_H_ */
