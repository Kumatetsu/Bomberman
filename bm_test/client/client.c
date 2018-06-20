#include "socket.h"
#include "client.h"

int main()
{
    int                 magic;
    int                 s;
    t_client_request*   client_request;

    srand(time(NULL));
    magic = (rand() % INT_MAX);
    s = create_client_socket();
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
    client_request->checksum = get_request_checksum(client_request);

    return client_request;
}

int free_client_request(t_client_request* client_request)
{
    free(client_request);
    if (client_request == NULL)
        return SUCCESS_FREE;
    return BAD_FREE;
}

int get_request_checksum(t_client_request* client_request)
{
    int checksum;

    checksum = 0;
    checksum = client_request->magic;
    checksum *= client_request->y_pos;
    checksum *= client_request->x_pos;
    checksum *= client_request->dir;
    checksum += client_request->command;
    checksum *= client_request->speed;
    checksum /= rand();

    return checksum;
}

char* request_serialization(t_client_request* client_request)
{
    char* request_string;

    client_request->checksum = get_request_checksum(client_request);
    request_string = (char*) client_request;

    return request_string;
}

t_client_request*   request_deserialize(char* request_serialized)
{
    t_client_request* client_request;

    client_request = (t_client_request*)request_serialized;

    return client_request;
};