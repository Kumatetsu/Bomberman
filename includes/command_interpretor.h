#ifndef _COMMAND_INTERPRETOR_H_
#define _COMMAND_INTERPRETOR_H_

#include "enum.h"
#include "server.h"
#include "client_request.h"

typedef struct s_command_interpretor
{
    enum COMMAND_REQUEST status;
    void (*f)(t_srv **, int);
} t_command_interpretor;

void command_interpretor(t_srv **server, t_player_request player_request);

#endif
