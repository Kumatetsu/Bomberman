#include "socket.h"
#include "server.h"

int accept_clients(t_srv **srv)
{
    t_srv_client *client;

    int			cs;
    int          i;
    int          j;
    struct sockaddr_in	client_sin;
    socklen_t		client_sin_len;

    j = 0;
    memset(&client_sin, 0, sizeof (struct sockaddr_in));
    client_sin_len = sizeof (client_sin);

    cs = accept((*srv)->fd, (struct sockaddr *)&client_sin, &client_sin_len);
    if (cs == -1){
        printf("we fucked up\n");
        return -1;
    }
    if (((t_srv *)srv)->clients[3] != NULL)
        return 0;
    client = create_srv_client(cs);

    for (i = 0; i < 4; i++)
    {
        if (((t_srv *)srv)->clients[i] != NULL)
            j++;
    }

    ((t_srv *)srv)->clients[j] = client;
    printf("cli accepted\n");
    return 0;
}
