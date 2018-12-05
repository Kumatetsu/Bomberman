/*
** socket.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:39:52 2018 hochar_n
** Last update Thu Jul  5 21:39:53 2018 hochar_n
*/

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

#endif
