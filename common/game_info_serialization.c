 /*
** game_info_serialization.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/common
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:33:54 2018 MASERA Mathieu
** Last update Wed Jul  4 09:33:55 2018 MASERA Mathieu
*/

#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "my_put.h"
#include "map.h"
#include "game_info.h"
#include "game_info_serialization.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char		*serialize_game_info()
{
  char		*game_info_str;
  t_game_info   *game_info;
  int		i;

  game_info = get_game_info();
  //game_info_str = malloc((sizeof(int) * 4) + sizeof(t_player_info) * 4 + sizeof(t_map_destroyable) * 14 * 15);
  game_info_str = malloc(sizeof(t_game_info));
  //maybe not good at all
  memcpy(game_info_str, &game_info->checksum, sizeof(int));
  memcpy(game_info_str + sizeof(int), &game_info->tick_time, sizeof(int));
  memcpy(game_info_str + sizeof(int) * 2, &game_info->game_status, sizeof(int));
  memcpy(game_info_str + sizeof(int) * 3, &game_info->id_client, sizeof(int));

  for(i=0; i < 4 ; i ++) {
    printf("server side bomb %d\n\n", game_info->players[i].bomb_left);
    if (i == 0)
      memcpy(game_info_str + (sizeof(int) * 4), &game_info->players[i], sizeof(t_player_info));
    else
      memcpy(game_info_str + (sizeof(int) * 4) + sizeof(t_player_info) * i, &game_info->players[i], sizeof(t_player_info));
  }

  //memcpy(game_info_str + sizeof(int) * 4 + sizeof(t_player_info) * 4, &game_info->map_destroyable, sizeof(t_map_destroyable) * 14 * 15);

  return game_info_str;
}

void		deserialize_game_info(char *serialized_game_info)
{
  t_game_info	*game_info;
  int		i = 0;

  game_info = malloc(sizeof(t_game_info));
  memcpy(&game_info->checksum, serialized_game_info, sizeof(int));
  memcpy(&game_info->tick_time, serialized_game_info + sizeof(int), sizeof(int));
  memcpy(&game_info->game_status, serialized_game_info + sizeof(int) * 2, sizeof(int));
  memcpy(&game_info->id_client, serialized_game_info + sizeof(int) * 3, sizeof(int));
  for (i =0; i < 4; i ++){
    if (i == 0)
      memcpy(&game_info->players[i], serialized_game_info + sizeof(int) * 4, sizeof(t_player_info));
    else
      memcpy(&game_info->players[i], serialized_game_info + sizeof(int) * 4 + sizeof(t_player_info) * i, sizeof(t_player_info));
  }
  //memcpy(game_info->map_destroyable, serialized_game_info + (sizeof(int) * 4) + sizeof(t_player_info) * 4, sizeof(t_map_destroyable) * 14 * 15);

  set_game_info(game_info);
}

int		get_game_info_checksum()
{
  int		checksum;
  unsigned char *p;
  t_game_info	*game_info;
  int		i;

  game_info = get_game_info();
  checksum = game_info->tick_time;
  p = (unsigned char *)&game_info->players;
  for (i = 0; i < (int)sizeof(game_info->players); i++)
    checksum += p[i];
  p = (unsigned char *)&game_info->game_status;
  for (i = 0; i < (int)sizeof(game_info->map_destroyable); i++)
    checksum += p[i];
  return checksum;
}
