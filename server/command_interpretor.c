#include "command_interpretor.h"
#include "notify_client.h"

static const t_command_interpretor commands[] =
    {
        {PLACE_BOMB, &notify_put_bomb},
        {MOVE_UP, &notify_move_up},
        {MOVE_DOWN, &notify_move_down},
        {MOVE_LEFT, &notify_move_left},
        {MOVE_RIGHT, &notify_move_right},
        {GIVE_PLAYERS, &notify_actual_players}};

void command_interpretor(t_srv **server, t_player_request player_request)
{
    int i;
    printf("server:in command_interpretor\n");
    for (i = 0; i < 8; i++)
    {
        printf("client command: %d, commands status: %d\n", player_request.command, commands[i].status);
        if (player_request.command == commands[i].status)
            commands[i].f(server, player_request.num_player);
    }
}
