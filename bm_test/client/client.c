#include "socket.h"
#include "client.h"

int main()
{
    int                 s;
    t_client_request*   client_request;

    s = create_client_socket();
    client_request = create_client_request();
    if (client_request == NULL)
        return 1;
    while(client_loop(s, client_request) == 1);
    free_client_request(client_request);
    printf("end of client\n");
    return 0;
}
