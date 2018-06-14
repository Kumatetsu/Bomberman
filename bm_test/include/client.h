#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <netinet/in.h>

typedef struct s_client
{
    unsigned int magic;
    int          me;
    sockaddr_in  to;
}               t_client;

typedef struct  s_client_request
{
  unsigned int  magic;                  /* Un magic number commun entre le client et le serveur, ou l'identifiant d'un type de structure */
  int           x_pos;                  /* La position x souhaitée par le client */
  int           y_pos;                  /* La position y souhaitée par le client */
  int           dir;                    /* La direction souhaitée par le client */
  int           command;                /* Une commande du client (0 : Ne rien faire / 1 : Poser une bombe) */
  int           speed;                  /* La vitesse du joueur */
  int           ckecksum;               /* Un checksum simple */
}               t_client_request;

#endif
