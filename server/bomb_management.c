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
//
#include "game_info.h"
#include "bomb_management.h"

int	index_to_x(int index)
{
  return (index % COLUMNS) * PIXEL_SIZE;
}

int	index_to_y(int index)
{
  int	y;

  y = index / COLUMNS;
  if (index % COLUMNS > 0)
    y++;
  return (y * PIXEL_SIZE); 
}

int	coord_to_index(int x, int y)
{
  int	index;
  int	col, line;

  // on trouve la colonne et la ligne, c'est tronqué
  col = x / PIXEL_SIZE;
  line = y / PIXEL_SIZE;
  // si c'est la dernière colonne de la ligne
  if (col == COLUMNS)
    // l'index est le nombre de ligne par le nombre de colonnes par ligne
    index = line * COLUMNS;
  else
    // sinon on retire une ligne, et on ajoute le nombre de colonnes en plus
    index = (line - 1) * COLUMNS + col;
  return index;
}

// retourne l'index de la matrice correspondant à un déplacement dans 'direction' de 'cases' cases
// depuis 'bomb', si le 'next_index' est hors map, on retourne -1
int     get_target(t_map_destroyable bomb, int direction, int cases)
{
  int	col, line, index, next_index;

  // on récupère l'index, la colonne et la ligne de la bombe
  index = coord_to_index(bomb.x, bomb.y);
  printf("\nget_target, coord_to_index with x = %d, y = %d: index = %d", bomb.x, bomb.y, index);
  printf("\nget_target, direction: %d, cases: %d", direction, cases);
  col = index % COLUMNS;
  line = index / COLUMNS;
  if (col < COLUMNS)
    line--;
  // retour par défaut -1
  next_index = -1;
  switch(direction)
    {
    case BOMBER_U:
      printf("\nget_target, direction: UP");
      if (line - cases > 0)
	next_index = index - COLUMNS * cases;
      break;
    case BOMBER_D:
      // pour uniformiser le retour on retourne -1 mais on aurait pu tester sur < 0 à la sortie
      printf("\nget_target, direction: DOWN");
      if (line + cases < LINES)
	next_index = index + COLUMNS * cases;
      break;
    case BOMBER_L:
      // si la colonne actuelle est inférieure aux nombre de cases souhaitées
      // pas la place donc on soustrait le nombre de case si on peut sinon return -1
      printf("\nget_target, direction: LEFT");
      if (col >= cases)
	next_index = index - cases; 
      break;
    case BOMBER_R:
      // si la colonne de la bombe est supérieure
      // au nombre total de colonnes moins le nombre de cases
      // il n'a pas la place , donc si col est inférieure on ajoute cases
      printf("\nget_target, direction: RIGHT");
      if (col < COLUMNS - cases)
	next_index = index + cases;
      break;
    }
  printf("\nget_target, next_index: %d", next_index);
  return next_index;
}

void		kill_player(int id)
{
  t_game_info	*game_info;
  
  game_info = get_game_info();
  game_info->players[id].dying = 3;
  game_info->players[id].alive = 0;
  game_info->players[id].bomb_left = 0;
}

// fire effect:
// wall: -1
// kill: index du joueur
// nothing: enum texture_type fire
int			check_fire_effect(t_map_destroyable case_in_fire)
{
  const SDL_Rect	sdl_target = pixel_rect(case_in_fire.x, case_in_fire.y);
  int			player;
  
  printf("\ncheck_fire_effect on x%d square %d:%d", PIXEL_SIZE, case_in_fire.x, case_in_fire.y);
  if (has_collision_with_wall(sdl_target))
    {
      printf("\ncheck_fire_effect: COLLISION WITH WALL");
      return -1;
    }
  if ((player = has_collision_with_player(sdl_target, -1)) >= 0)
    {
      printf("\ncheck_fire_effect: COLLISION WITH PLAYER: %d", player);
      kill_player(player);
      return player;
    }
  return fire;
}

void			boom(t_map_destroyable *map_destroyable, int i)
{
  t_map_destroyable	boom_origin;
  int			target, effect;
  int			iterator, it;

  effect = -1;
  target = -1;
  boom_origin = map_destroyable[i];
  boom_origin.fire[BOMBER_U] = 0;
  boom_origin.fire[BOMBER_D] = 0;
  boom_origin.fire[BOMBER_L] = 0;
  boom_origin.fire[BOMBER_R] = 0;
  for (iterator = 1; iterator <= 3; iterator++)
    {
      // pour chaque direction on appelle une fonction capable de tester si
      // on peut avancer d'1, 2 ou 3 
      // on applique check_fire_effect qui gère les murs et les kills
      for (it = 0; it < 4; it++)
	{
	  target = get_target(boom_origin, it, iterator);
	  printf("\ndirection = %d, cases = %d, target = %d", it, iterator, target);
	  if (target != -1)
	    {
	      map_destroyable[target].x = index_to_x(target);
	      map_destroyable[target].y = index_to_y(target);
	      // it = direction
	      // iterator = cases souhaitées depuis le point d'origine
	      // si le précédent tour pour cette direction à validé la présence
	      // d'une explosion sur la case 'target', le fire[it] correspondant
	      // DOIT être égal à iterator - 1, si ce n'est pas le cas, c'est
	      // que le précédent effect était un wall. Dans ce cas, on ne souhaite pas appellé
	      // check_fire_effect (car on ne veut pas tuer un joueur derrière un mur)
	      // d'où l'ordre de la condition.
	      if (boom_origin.fire[it] == iterator - 1
		  && (effect = check_fire_effect(map_destroyable[target])) != -1)
		boom_origin.fire[it] = iterator;
	    }
	}
      // DEV
      for (it = 0; it < 4; it++)
	{
	  printf("\nPour it = %d, boom_origin.fire[it] == %d\n", it, boom_origin.fire[it]);
	}
      //
      map_destroyable[i] = boom_origin;
    }
}
