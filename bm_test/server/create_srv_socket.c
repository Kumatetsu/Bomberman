#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int create_server_socket()
{
    int s;
    struct sockaddr_in sin;
    int port;

    memset(&sin, 0, sizeof(struct sockaddr_in));
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        return (-1);

    port = 4022;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1)
        return (-1);
    if (listen(s, 42) == -1)
        return (-1);

    return s;
}
