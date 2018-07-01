#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "request.h"

t_player_request* 	create_player_request();
int 			free_player_request(t_player_request* client_request);
int 			client_loop(int s);
void			my_bzero(void *s1, int n);

#endif
