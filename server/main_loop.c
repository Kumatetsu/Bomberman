/*
** main_loop.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/server
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:37:32 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:33 2018 MASERA Mathieu
*/

#include <stdio.h>
#include <sys/time.h>
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "request_serialization.h"
#include "player_info.h"
#include "server.h"
#include "player.h"
#include "map.h"
#include "game_info.h"
#include "my_put.h"
#include "request_handling.h"
#include "main_loop.h"
#include "response_type_utils.h"
#include "server_request.h"
#include "notify_client.h"
#include "command_interpretor.h"

void restart_game(t_srv **srv)
{
    t_game_info *game_info;

    game_info = get_game_info();
    reset_players(srv);
    for (int i = 0; i < 4; i++)
    {
        game_info->players[i] = (*srv)->players[i];
    }
    game_info->game_status = 1;
    (*srv)->running = 1;
}

int main_loop(t_srv **srv)
{
    int i;
    int error;
    socklen_t len;
    int retval;
    // int			response_type;
    struct timeval it_value;
    t_player_request player_request = {0};
    int survivors;

    printf("\nMAIN_LOOP\n");
    i = 0;
    // On initialise direct la game_info
    // on utilise ensuite is_running() pour savoir si ca tourne
    // puis on récupère la static remplie
    FD_ZERO(&(*srv)->fd_read);
    FD_SET((*srv)->fd, &(*srv)->fd_read);
    // server.h définition du fd max pour le select, defaut dans init_server
    for (i = 0; i < 4; i++)
    {
        if ((*srv)->players[i].connected == 1)
        {
            FD_SET((*srv)->players[i].fd, &(*srv)->fd_read);
            if ((*srv)->players[i].fd > (*srv)->fd_max)
                (*srv)->fd_max = (*srv)->players[i].fd;
        }
    }

    it_value.tv_sec = 6;
    it_value.tv_usec = 0;
    if (select((*srv)->fd_max + 1, &(*srv)->fd_read, NULL, NULL, &it_value) == -1)
        return (0);

    if (!server_is_full(srv))
    {
        // ici on accepte les connections clientes
        if (FD_ISSET((*srv)->fd, &(*srv)->fd_read))
        {
            // player.h
            if ((i = accept_players(srv)) == -1)
                return 0;
        }
    }

    if (is_enought_players(srv) && (*srv)->game_status != 1)
    {
        // server.h
        // set le game_status à 1
        // copie les joueurs dans la game_info
        // passe le connected à 1 pour tous
        // définis le placement
        printf("\nStart Game\n");
        (*srv)->game_status = 1;
        // start_game(srv);
        //
    }
    survivors = 0;
    // pour les joueurs... 0 à 3
    for (i = 0; i < 4; i++)
    {
        // Si le joueur est connecté... (c'est set à 1 dans server/create_game.c::create_game_info)
        if ((*srv)->players[i].connected == 1)
        {
            error = 0;
            len = sizeof(error);
            // interroge les options de la socket (player->fd) pour détecter une erreur
            retval = getsockopt((*srv)->players[i].fd, SOL_SOCKET, SO_ERROR, &error, &len);
            // Si erreur on déco le player, ca évite de réitérer dessus
            if (retval != 0 || error != 0)
            {
                (*srv)->players[i].connected = 0;
                continue;
            }
            // Si la socket du player est set on traite...
            if (FD_ISSET((*srv)->players[i].fd, &(*srv)->fd_read))
            {
                int n = 0;
                // char buffer[sizeof(int)];
                int buffer;
                printf("\nHandling request for player\n");
                // On extrait le contenu
                if ((n = recv((*srv)->players[i].fd, &buffer, sizeof(int), 0)) > 0)
                {
                    // if ((*srv)->game_status != RUNNING)
                    //     continue;

                    player_request.command = ntohl(buffer);
                    player_request.num_player = i;
                    printf("server: num player %d and command %d", player_request.num_player, player_request.command);
                    command_interpretor(srv, player_request);
                    // else
                    // {
                    //     printf("\nCLIENT REQUEST COMMAND: %d\n", player_request.command);
                    //     // handle_requests(game_info, &player_request);

                    //     // response_type = define_response_type(player_request.command);
                    //     response_pos.id = MOVE;
                    //     response_pos.x = 0;
                    //     response_pos.y = 0;

                    //     write((*srv)->players[i].fd, &response_pos, sizeof(response_pos));
                    // }
                }
                printf("client send request\n");
            }
        }
        if ((*srv)->players[i].alive)
            survivors++;
    }
    if ((*srv)->game_status == RUNNING && survivors <= 1)
    {

        (*srv)->game_status = ENDGAME;
        (*srv)->running = ENDGAME;
        printf("\nENDGAME\n");
        restart_game(srv);
    }
    return (1);
}
