#include "command_interpretor.h"
#include "update_client.h"

static const t_client_interpretor client_commands[] =
    {
        {MOVE_U, &update_pos},
        {MOVE_L, &update_pos},
        {MOVE_R, &update_pos},
        {MOVE_D, &update_pos},
        {BOMB, &update_bomb},
        {ENDEXPLOSION, &update_explosion},
        {PLAYERS, &update_players},
        {EXPLOSION, &update_explosion}};

void client_interpretor(t_game_info **game_info, t_response_pool *response_pool)
{
    int i;
    printf("client: in client_interpretor\n");
    for (i = 0; i < 8; i++)
    {
        if (response_pool->id == client_commands[i].status)
        {
            client_commands[i].f(game_info, response_pool);
            return;
        }
    }
}
