#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int create_client_socket()
{
    struct sockaddr_in sin;
    int s;
    int port;

    memset(&sin, 0, sizeof(struct sockaddr_in));
    port = 4022;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        return (-1);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        printf("Error connect()\n");
        return (-1);
    }
    printf("connected\n");

    return s;
}
