/*
** client_get_game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Mon Jul  2 16:17:01 2018 BILLAUD Jean
** Last update Mon Jul  2 18:02:55 2018 BILLAUD Jean
*/

#include "sdl.h"
#include "client.h"
#include "game_info.h"
#include "game_info_serialization.h"

int get_message(int s)
{
  char buff[sizeof(t_game_info)];
  int r;
  t_game_info *game_info;

  game_info = NULL;
  r = recv(s, buff, sizeof(t_game_info), 0);
  if (r > 0)
  {
    deserialize_game_info(buff);
    game_info = get_game_info();
    printf("%d \n", game_info->game_status);
    printf("%d \n", game_info->tick_time);
    printf("%ld \n", (long int)game_info->checksum);
    printf("%d \n", game_info->players[0]->num_player);
    return 1;
  }
  else
    return 0;
}
