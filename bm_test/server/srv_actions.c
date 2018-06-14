#include "socket.h"
#include "server.h"

int accept_clients(t_srv **srv)
{
    printf("waiting\n");
    t_srv_client *client;

    int			cs;
    struct sockaddr_in	client_sin;
    socklen_t		client_sin_len;

    memset(&client_sin, 0, sizeof (struct sockaddr_in));
    client_sin_len = sizeof (client_sin);

    cs = accept((*srv)->fd, (struct sockaddr *)&client_sin, &client_sin_len);
    if (cs == -1){
        printf("we fucked up\n");
        return -1;
    }

    client = create_srv_client(cs);
    ((t_srv *)srv)->clients[0] = client;
    return 0;
}
