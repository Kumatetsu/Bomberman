/*
** create_game.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Tue Jul  3 22:29:46 2018 hochar_n
*/

#include "system.h"
#include "socket.h"
#include "server.h"
#include "thread.h"
#include "game_info.h"
#include "my_put.h"

void			create_game_info(t_srv **srv)
{
  t_game_info 		*game_info;
  t_map_destroyable 	map_destroyable;
  int 			i;
  int 			x;
  int			y;

  game_info = get_game_info();
  game_info->game_status = 1;
  for (i = 0; i < 3; ++i)
    {
      game_info->players[i] = (*srv)->players[i];
      if (game_info->players[i].connected == 0)
        continue;
      game_info->players[i].connected = 1;
      game_info->players[i].bomb_left = 1;
      game_info->players[i].num_player = i + 1;
      specify_player_info(i, game_info);
    }
  for (i = 0; i < 32; ++i)
    {
      map_destroyable.exist = 1;
      map_destroyable.wall_destroyable = 1;
      x = random_at_most(13);
      y = random_at_most(11);
      map_destroyable.y_pos = y * 8;
      map_destroyable.x_pos = x * 8;
      game_info->map_destroyable[y][x] =  map_destroyable;
    }
}

void    specify_player_info(int i, t_game_info *game_info)
{
  switch (i)
    {
    case 0:
      game_info->players[i].x_pos = 2;
      game_info->players[i].y_pos = 2;
      game_info->players[i].current_dir = BOMBER_L;
      break;
    case 1:
      game_info->players[i].x_pos = 101;
      game_info->players[i].y_pos = 2;
      game_info->players[i].current_dir = BOMBER_D;
      break;
    case 2:
      game_info->players[i].x_pos = 2;
      game_info->players[i].y_pos = 85;
      game_info->players[i].current_dir = BOMBER_U;
      break;
    case 3:
      game_info->players[i].x_pos = 101;
      game_info->players[i].y_pos = 85;
      game_info->players[i].current_dir = BOMBER_R;
      break;
    }
}

long random_at_most(long max)
{
  unsigned long num_bins = (unsigned long) max + 1;
  unsigned long num_rand = (unsigned long) RAND_MAX + 1;
  unsigned long bin_size = num_rand / num_bins;
  unsigned long defect = num_rand % num_bins;

  int x;
  do {
    x = rand();
  } while (num_rand - defect <= (unsigned long) x);

  return x / bin_size;
}
