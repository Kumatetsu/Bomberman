#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

typedef struct  s_client_request
{
	int           checksum;               /* Un checksum simple */
	unsigned int  magic;                  /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
	int           y_pos;                  /* La position y souhaitée par le client */
	int           x_pos;                  /* La position x souhaitée par le client */
	int           dir;                    /* La direction souhaitée par le client */
	int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
	int           speed;                  /* La vitesse du joueur */
}               t_client_request;

enum CLIENT_REQUEST_STATUS
{
	BAD_SEND,
	SUCCESS_SEND,
	BAD_RECEIVE,
	SUCCESS_RECEIVE,
	BAD_FREE,
	SUCCESS_FREE
};

t_client_request* 	init_make_base_request();
int 	client_loop(int s, t_client_request* client_request);
char* 	request_serialization(t_client_request* client_request);
t_client_request* request_deserialize(char* serialized_request);
int 	free_client_request(t_client_request* client_request);
int		get_request_checksum(t_client_request* client_request);
void	my_bzero(void *s1, int n);


#endif
