/*
** game_info.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/common
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:33:09 2018 MASERA Mathieu
** Last update Wed Jul  4 09:33:11 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include "server.h"
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

int	is_running()
{
  return game_info->game_status;
}

void    start_game(t_srv **srv)
{
  int	i;

  game_info->game_status = 1;
  for (i = 0; i < 4; ++i)
    {
      game_info->players[i] = (*srv)->players[i];
      active_player(&(game_info->players[i]));
    }
}

void                    create_game_info()
{
  t_map_destroyable     map_destroyable;
  int                   i;
  int                   x;
  int                   y;
  
  game_info->game_status = 0;
  for (i = 0; i < 32; ++i)
    {
      x = random_at_most(13);
      y = random_at_most(11);
      map_destroyable.y_pos = y * 8;
      map_destroyable.x_pos = x * 8;
      map_destroyable.bomb = 0;
      map_destroyable.bomb_owner = -1;
      map_destroyable.dying = 0;
      map_destroyable.start_explode = 0;
      map_destroyable.wall_destroyable = 1;
      map_destroyable.exist = 1;
      game_info->map_destroyable[y][x] =  map_destroyable;
    }
}

void    active_player(t_player_info *player)
{
  player->connected = 1;
  switch (player->num_player)
    {
    case 0:
      player->x_pos = 2;
      player->y_pos = 2;
      player->current_dir = BOMBER_L;
      break;
    case 1:
      player->x_pos = 101;
      player->y_pos = 2;
      player->current_dir = BOMBER_D;
      break;
    case 2:
      player->x_pos = 2;
      player->y_pos = 85;
      player->current_dir = BOMBER_U;
      break;
    case 3:
      player->x_pos = 101;
      player->y_pos = 85;
      player->current_dir = BOMBER_R;
      break;
    }
}

long random_at_most(long max)
{
  unsigned long num_bins = (unsigned long) max + 1;
  unsigned long num_rand = (unsigned long) RAND_MAX + 1;
  unsigned long bin_size = num_rand / num_bins;
  unsigned long defect = num_rand % num_bins;
  long x;
  do {
    x = random();
  } while (num_rand - defect <= (unsigned long) x);
  return x / bin_size;
}
