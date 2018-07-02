#ifndef _SOCKET_H
#define _SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int create_client_socket();
int create_server_socket();

#endif /* !_SOCKET_H_ */
