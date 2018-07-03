#include "player.h"
#include "request.h"
#include "sdl.h"
#include "game_info.h"
#include "game_info_serialization.h"

char		*serialize_game_info()
{
  char		*game_info_str;
  t_game_info	*game_info;

  game_info = get_game_info();
  if ((game_info_str = calloc(1, sizeof(t_game_info))) == NULL)
    return NULL;
  game_info_str = (char*) game_info;
  if ((game_info_str = realloc(game_info_str, sizeof(t_game_info) + 1)) == NULL)
    return NULL;
  game_info_str[sizeof(t_game_info)] = '\0';
  return game_info_str;
}

void		deserialize_game_info(char *serialized_game_info)
{
  t_game_info	*game_info;
  
  game_info = (t_game_info*) serialized_game_info;
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

