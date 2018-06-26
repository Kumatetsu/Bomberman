#include "socket.h"
#include "client.h"

int main()
{
    int                 s;
    t_player_request*   client_request;

    s = create_client_socket();
    client_request = create_player_request();
    if (client_request == NULL)
        return 1;
    while(client_loop(s, client_request) == 1);
    free_player_request(client_request);
    printf("end of client\n");
    return 0;
}
