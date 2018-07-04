/*
** game_info_serialization.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/common
** 
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
** 
** Started on  Wed Jul  4 09:33:54 2018 MASERA Mathieu
** Last update Wed Jul  4 09:33:55 2018 MASERA Mathieu
*/

#include "player.h"
#include "request.h"
#include "sdl.h"
#include "game_info.h"
#include "game_info_serialization.h"

char		*serialize_game_info()
{
  char		*game_info_str;
  t_game_info	*game_info;
  t_player_info		*players[4];
  t_map_destroyable	*map_destroyable[14][15];
  char              *tmp;

  game_info = get_game_info();
  tmp = malloc((sizeof(int) * 4) + sizeof(players) + sizeof(map_destroyable));

  //maybe not good at all
  memcpy(tmp, &game_info, sizeof(int) * 4);
  memcpy(tmp + (sizeof(int) * 4), &game_info->players, sizeof(players));
  memcpy(tmp + ((sizeof(int) * 4) + sizeof(players)), &game_info->map_destroyable, sizeof(map_destroyable));

  if ((game_info_str = calloc(1, (sizeof(int) * 4) + sizeof(players) + sizeof(map_destroyable) + 1)) == NULL)
    return NULL;
  game_info_str = (char*) tmp;
  printf("before realloc\n");

  if ((game_info_str = (char*)realloc(game_info_str, sizeof(int) * 4) + sizeof(players) + sizeof(map_destroyable) + 1) == NULL)
    return NULL;
  game_info_str[(sizeof(int) * 4) + sizeof(players) + sizeof(map_destroyable) + 1] = '\0';

  free(tmp);
  printf("before return\n");
  return game_info_str;
}

void		deserialize_game_info(char *serialized_game_info)
{
  t_game_info	*game_info;

  game_info = calloc(1, sizeof(t_game_info));

  memcpy(game_info, &serialized_game_info, sizeof(int));
  memcpy(game_info + sizeof(int), &serialized_game_info[sizeof(int)], sizeof(int));
  memcpy(game_info + (sizeof(int) * 2), &serialized_game_info[sizeof(int) * 2], sizeof(int));
  memcpy(game_info + (sizeof(int) * 3), &serialized_game_info[sizeof(int) * 3], sizeof(int));
  memcpy(game_info + (sizeof(int) * 4), &serialized_game_info[sizeof(int) * 4], sizeof(t_player_info));
  memcpy(game_info + (sizeof(int) * 4 + sizeof(t_player_info)), &serialized_game_info[(sizeof(int) * 4) + sizeof(t_player_info)], sizeof(t_map_destroyable));

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
