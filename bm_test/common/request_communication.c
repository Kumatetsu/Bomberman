#include "socket.h"
#include "client.h"

int get_request_checksum(t_player_request* client_request)
{
	int checksum = 0;

	unsigned char *p = (unsigned char *)&client_request->magic;
	for (int i=0; i<(int)sizeof(client_request->magic); i++) {
		checksum += p[i];
	}
	p = (unsigned char *)&client_request->y_pos;
	for (int i=0; i<(int)sizeof(client_request->y_pos); i++)
		checksum += p[i];
	p = (unsigned char *)&client_request->x_pos;
	for (int i=0; i<(int)sizeof(client_request->x_pos); i++)
		checksum += p[i];
	p = (unsigned char *)&client_request->dir;
	for (int i=0; i<(int)sizeof(client_request->dir); i++)
		checksum += p[i];
	p = (unsigned char *)&client_request->command;
	for (int i=0; i<(int)sizeof(client_request->command); i++)
		checksum += p[i];
	p = (unsigned char *)&client_request->speed;
	for (int i=0; i<(int)sizeof(client_request->speed); i++)
		checksum += p[i];

	return checksum;
}

char* request_serialization(t_player_request* client_request)
{
	char* request_string;

	request_string = calloc(1, sizeof(t_player_request));
	if (request_string == NULL)
		return NULL;
	client_request->checksum = get_request_checksum(client_request);
	request_string = (char*) client_request;
	request_string = realloc(request_string,sizeof(t_player_request)+1);
	if (request_string == NULL)
		return NULL;
	request_string[sizeof(t_player_request)] = '\0';

	return request_string;
}

t_player_request*   request_deserialize(char* request_serialized)
{
	t_player_request* client_request;

	client_request = (t_player_request*)request_serialized;

	return client_request;
}