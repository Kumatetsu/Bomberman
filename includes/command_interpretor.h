#ifndef _COMMAND_INTERPRETOR_H_
#define _COMMAND_INTERPRETOR_H_

#include "enum.h"
#include "server.h"
#include "game_info.h"
#include "server_request.h"
#include "client_request.h"

typedef struct s_command_interpretor
{
    enum COMMAND_REQUEST status;
    void (*f)(t_srv **, int);
} t_command_interpretor;

typedef struct s_client_interpretor
{
    enum Response_type status;
    void (*f)(t_game_info **, t_response_pool *);
} t_client_interpretor;

void command_interpretor(t_srv **server, t_player_request player_request);
void client_interpretor(t_game_info **game_info, t_response_pool *response_pool);

#endif
