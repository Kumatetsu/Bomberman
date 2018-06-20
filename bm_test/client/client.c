#include "socket.h"
#include "client.h"

int main()
{
    int s;
    s = create_client_socket();
    while(client_loop(s));
    printf("end of client\n");
    return 0;
}
