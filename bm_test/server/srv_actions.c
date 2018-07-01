/*
** srv_actions.c for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:45:57 2018 hochar_n
** Last update Sun Jul  1 17:46:02 2018 hochar_n
*/

#include "socket.h"
#include "server.h"

int			accept_clients(t_srv **srv)
{
    t_player_info	*client;
    int			cs;
    int			i;
    int			j;
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
    if ((*srv)->clients[3] != NULL
        || (*srv)->n_clients > 3
        || (*srv)->game_info != NULL)
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
    (*srv)->n_clients++;
    printf("%d\n", j);
    printf("%d\n", (*srv)->clients[j]->fd);
    printf("cli accepted\n");
    return 0;
}

t_player_info       *create_player(int fd)
{
    t_player_info   *player;

    if ((player = malloc(sizeof (*player))) == 0)
        return NULL;

    player->fd = fd;

    return player;
}
