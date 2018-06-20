#include "socket.h"
#include "client.h"

int main()
{
    int                 magic;
    int                 s;
    t_client_request*   client_request;
    char*               serelialized;

    srand(time(NULL));
    magic = (rand() % INT_MAX);
    s = create_client_socket();
    client_request = init_make_base_request(magic);
    if (client_request == NULL)
        return 1;
    printf("The checksum is %d and the magic is %d\n", get_request_checksum(client_request), client_request->magic);
    serelialized = request_serialization(client_request);
    printf("The serialization is %s\n", serelialized);
    client_request = request_deserialize(serelialized);
    printf("The checksum is %d and the magic is %d\n", get_request_checksum(client_request), client_request->magic);
    while(client_loop(s, client_request) == 1);
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
    int checksum = 0;

    unsigned char *p = (unsigned char *)&client_request->magic;
    for (int i=0; i<(int)sizeof(client_request->magic); i++) {
        checksum += p[i];
    }
    p = (unsigned char *)&client_request->y_pos;
    for (int i=0; i<(int)sizeof(client_request->y_pos); i++) {
        checksum += p[i];
    }
    p = (unsigned char *)&client_request->x_pos;
    for (int i=0; i<(int)sizeof(client_request->x_pos); i++) {
        checksum += p[i];
    }

    p = (unsigned char *)&client_request->dir;
    for (int i=0; i<(int)sizeof(client_request->dir); i++) {
        checksum += p[i];
    }

    p = (unsigned char *)&client_request->command;
    for (int i=0; i<(int)sizeof(client_request->command); i++) {
        checksum += p[i];
    }

    p = (unsigned char *)&client_request->speed;
    for (int i=0; i<(int)sizeof(client_request->speed); i++) {
        checksum += p[i];
    }

    return checksum;
}

char* request_serialization(t_client_request* client_request)
{
    char* request_string;

    request_string = calloc(1, sizeof(t_client_request));
    if (request_string == NULL)
        return NULL;
    client_request->checksum = get_request_checksum(client_request);
    request_string = (char*) client_request;
    request_string = realloc(request_string,sizeof(t_client_request)+1);
    if (request_string == NULL)
        return NULL;
    request_string[sizeof(t_client_request)] = '\0';

    return request_string;
}

t_client_request*   request_deserialize(char* request_serialized)
{
    t_client_request* client_request;

    client_request = (t_client_request*)request_serialized;

    return client_request;
}