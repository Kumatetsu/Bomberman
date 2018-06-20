#include "socket.h"
#include "client.h"

int main()
{
    int                 magic;
    int                 s;
    t_client_request*   client_request;

    srand(time(NULL));
    magic = rand() % INT_MAX;
    s = create_client_socket(magic);
    client_request = init_make_base_request(magic);
    if (client_request == NULL)
        return 1;
    while(client_loop(s, client_request));
    free_client_request(client_request);
    printf("end of client\n");
    return 0;
}

t_client_request*       init_make_base_request(unsigned int magic)
{
    t_client_request*   client_request;

    client_request = calloc(1, sizeof(t_client_request));
    if (client_request == NULL)
        return NULL;

    client_request->magic = magic;
    client_request->ckecksum = get_request_checksum(client_request);

    return client_request;
}

int free_client_request(t_client_request* client_request)
{
    free(client_request);
    if (client_request == NULL)
        return SUCCESS_FREE;
    return BAD_FREE;
}

int get_request_ckecksum(t_client_request* client_request)
{
    int ckecksum;

    ckecksum = 0;
    ckecksum = client_request->magic;
    ckecksum *= client_request->y_pos;
    ckecksum *= client_request->x_pos;
    ckecksum *= client_request->dir;
    ckecksum += client_request->command;
    ckecksum *= client_request->speed;
    ckecksum /= rand();

    return ckecksum;
}

char* get_request_string(t_client_request* client_request)
{
    client_request->ckecksum = get_request_ckecksum(client_request);

    return (char*) client_request;
}