#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct  s_client_request
{
  unsigned int  magic;                  /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
  int           y_pos;                  /* La position y souhaitée par le client */
  int           x_pos;                  /* La position x souhaitée par le client */
  int           dir;                    /* La direction souhaitée par le client */
  int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  int           speed;                  /* La vitesse du joueur */
  int           ckecksum;               /* Un checksum simple */
}               t_client_request;

int client_loop(int s);

#endif
