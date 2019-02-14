#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "map.h"
#include "player_info.h"
#include "base_map_manager.h"
#include "collision.h"
// pour game_info.h
#include "client_request.h"
#include "server.h"
#include "game_info.h"
#include "coord_index_swapper.h"
#include "bomb_management.h"
#include <stdio.h>

// return the matrice index which correspond to a move in the direction of squares
// from 'square', if the 'next index' is out of map we return -1
int	get_target(t_map_destroyable bomb, int direction, int cases)
{
  int	col, line, index, next_index;

  // we get back the index, the column and the bomb line
  index = coord_to_index(bomb.x, bomb.y);
  col = (index + 1) % COLUMNS;
  line = (index + 1) / COLUMNS;
  if (col != 0) {
    line++;
  }
  // return by default constant OUTOFMAP
  next_index = OUTOFMAP;
  switch (direction)
    {
    case BOMBER_D:
      //to uniformise the return we return -1
      if (line + cases < LINES) {
	next_index = index + COLUMNS * cases;
      }
      break;
    case BOMBER_L:
      // if the actual column is inferior to the number of square wished
      // we don't have enough place so we substract the number of case if we can else we return -1
      if (col >= cases) {
	next_index = index - cases;
      }
      break;
    case BOMBER_R:
      // if the column is upper to the total number of column less the number of square
      // there is not enought place, so if columns are less we add squares
      if (col < COLUMNS - cases) {
	next_index = index + cases;
      }
      break;
    case BOMBER_U:
      if (line - cases > 0) {
	next_index = index - COLUMNS * cases;
      }
      break;
    }
  return (next_index);
}

void kill_player(t_srv **srv, int id)
{
  (*srv)->players[id].dying = 0;
  (*srv)->players[id].alive = 0;
  (*srv)->players[id].x = -50;
  (*srv)->players[id].bomb_left = -50;
  printf("\nSERVER, bomb_management: player %d killed\n", id);
}

// fire effect:
// wall: -1
// kill: index of the player
// nothing: enum texture_type fire
int			check_fire_effect(t_srv **srv, t_map_destroyable case_in_fire)
{
  // we reduce the square of collision control to be sure it does not impact with everything
  // on vérifie avec un carré de 16x16 avec 16 de margin
  const SDL_Rect	sdl_target = init_rect(case_in_fire.x + 16, case_in_fire.y + 16, 16, 16);
  int			player = 0;

  if (has_collision_with_wall(sdl_target))
    {
      return (-1);
    }
  if ((player = has_collision_with_player(srv, sdl_target, -1)) >= 0)
    {
      kill_player(srv, player);
      return (player);
    }
  return (fire);
}

void			boom(t_srv **srv, int indexes[13])
{
  t_map_destroyable	boom_origin;
  int			target, effect;
  int			iterator, it;
  int			k;

  k = 0;
  effect = -1;
  target = -1;
  boom_origin = (*srv)->map_destroyable[indexes[0]];
  boom_origin.fire[BOMBER_U] = 0;
  boom_origin.fire[BOMBER_D] = 0;
  boom_origin.fire[BOMBER_L] = 0;
  boom_origin.fire[BOMBER_R] = 0;
  for (iterator = 1; iterator <= 3; iterator++)
    {
      // foreach direction we call a function which can test if we can
      // move on 1, 2 or 3. We apply check_fire_effect which manage walls and kills
      for (it = 0; it < 4; it++)
	{
	  k += 1;
	  target = get_target(boom_origin, it, iterator);
	  indexes[k] = target;
	  if (target != OUTOFMAP)
	    {
	      // it = direction
	      // iterator = squares wished from the origin point
	      // if the previous turn this direction validated that there is an explosion
	      // on the square 'target', the corresponding fire[it] MUST
	      // be equal to 'iterator' -1, if not, this means the previous effect was a wall.
	      // In this case, we don't wish to call check_fire_effect because we don't want to 
	      // kill a player which is behind a wall (which explain the order of the statements)
	      (*srv)->map_destroyable[target].x = index_to_x(target);
	      (*srv)->map_destroyable[target].y = index_to_y(target);
	      if (boom_origin.fire[it] == iterator - 1 && (effect = check_fire_effect(srv, (*srv)->map_destroyable[target])) != -1) {
		boom_origin.fire[it] = iterator;
		(*srv)->map_destroyable[target].exist = 1;
		(*srv)->map_destroyable[target].explosion_stage = 5;
		(*srv)->map_destroyable[target].start_explode = 0;
	      }
	    }
	}
      boom_origin.bomb = 0;
      boom_origin.start_explode = 0;
      boom_origin.explosion_stage = 5;
      (*srv)->map_destroyable[indexes[0]] = boom_origin;
    }
}
