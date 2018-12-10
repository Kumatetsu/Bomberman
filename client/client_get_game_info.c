/*
** client_get_game_info.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Mon Jul  2 16:17:01 2018 BILLAUD Jean
** Last update Wed Jul  4 10:16:22 2018 MASERA Mathieu
*/

#include "sdl.h"
#include "client.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include "my_put.h"

int get_message(int s)
{
  char buff[sizeof(t_game_info)];
  int r;
  t_game_info *game_info;
  int i;

  game_info = NULL;
  r = recv(s, buff, sizeof(t_game_info) - 1 , 0);
  if (r > 0)
  {
    //deserialize_game_info(buff);
    game_info = (t_game_info*)buff;
    set_game_info(game_info);
    //game_info = get_game_info();
    printf("tick_time %d \n", game_info->tick_time);
    for (i=0; i<4; i++) {
      if (&game_info->players[i]) {
        printf("client fd %d\n\n", (int)game_info->players[i].fd);
        printf("client xpos: %d\n\n", (int)game_info->players[i].x_pos);
        printf("client ypos: %d\n\n", (int)game_info->players[i].y_pos);
      }
    }
    return 1;
  }
  else
    return 0;
}
