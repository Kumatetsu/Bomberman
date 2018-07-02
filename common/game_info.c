#include <stdlib.h>
#include "player.h"
#include "request.h"
#include "sdl.h"
#include "game_info.h"

static t_game_info *game_info;

t_game_info	*get_game_info()
{
  return game_info;
}

void	set_game_info(t_game_info *new_game_info)
{
  game_info = new_game_info;
}
