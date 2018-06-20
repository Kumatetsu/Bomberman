#include "socket.h"
#include "server.h"

int accept_clients(t_srv **srv)
{
    t_player_infos *client;

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
    if ((*srv)->clients[3] != NULL)
        return 0;

    client = create_player(cs);
    if (NULL == client)
        return -1;
    for (i = 0; i < 4; i++)
    {
        if ((*srv)->clients[i] != NULL)
        {
            j += 1;
        }
    }

    client->connected = 1;
    client->alive = 1;
    (*srv)->clients[j] = client;
    printf("%d\n", j);
    printf("%d\n", (*srv)->clients[j]->fd);
    printf("cli accepted\n");
    return 0;
}

t_player_infos        *create_player(int fd)
{
    t_player_infos  *player;

    if ((player = malloc(sizeof (*player))) == 0)
        return NULL;

    player->fd = fd;

    return player;
}
