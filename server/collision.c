#include <stdio.h>
#include "enum.h"
#include "constant.h"
// pour game_info.h
#include "sdl.h" // pour player_info.h et collision.h
//
#include "player_info.h"
#include "map.h"
#include "client_request.h" // pour server.h
#include "server.h"
//
#include "game_info.h"
#include "static_wall_rect.h"
#include "collision.h"

int		has_collision_with_wall(const SDL_Rect zone)
{
  int		i;
  SDL_Rect	*walls;

  walls = get_walls();
  for (i = 0; i < 82; i++)
  {
    if (SDL_HasIntersection(&zone, &walls[i])) {
      return (1);
    }
  }
  return (0);
}

int	has_collision_with_destructible(t_srv **srv, const SDL_Rect zone)
{
  int	i;

  for (i = 0; i < INLINE_MATRIX; i++)
  {
    if (!(*srv)->map_destroyable[i].exist && !(*srv)->map_destroyable[i].bomb) {
      continue;
    }
    const SDL_Rect element = {(*srv)->map_destroyable[i].x, (*srv)->map_destroyable[i].y, PIXEL_SIZE, PIXEL_SIZE};
    if (SDL_HasIntersection(&zone, &element)) {
      printf("COLLISION WITH: index:%d exist:%d", i, (*srv)->map_destroyable[i].exist);
      return (1);
    }
  }
  return (0);
}

// return -1 if no collision, else the player's number
int	has_collision_with_player(t_srv **srv, const SDL_Rect zone, int num_player)
{
  int	y;
  // Loop over players
  for (y = 0; y < (int)(sizeof((*srv)->players) / sizeof((*srv)->players[0])); ++y)
  {
    // if we didn't give -1 as num_player, we don't check with the player who as the same id
    if ((-1 == num_player || (*srv)->players[y].num_player != num_player) && &(*srv)->players[y] != NULL)
    {
      //printf("\nin players stuff\n");
      const SDL_Rect other_player = {(*srv)->players[y].x, (*srv)->players[y].y, PIXEL_SIZE, PIXEL_SIZE};
      if (SDL_HasIntersection(&zone, &other_player)) {
        return ((*srv)->players[y].num_player);
      }
    }
  }
  return (-1);
}
