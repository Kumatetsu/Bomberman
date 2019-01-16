#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "map.h"
#include "game_info.h"

int	index_to_x(int index)
{
  return index % COLUMNS;
}

int	index_to_y(int index)
{
  int	y;

  y = index / COLUMNS;
  if (index % COLUMNS > 0)
    y++;
  return y; 
}

int	coord_to_index(int x, int y)
{
  int	index;
  int	col, line;

  // on trouve la colonne et la ligne
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

int     get_target(t_map_destroyable *map, t_map_destroyable bomb, int direction, int cases)
{
  int	col, line, index, next_index;

  // on récupère l'index, la colonne et la ligne de la bombe
  index = coord_to_index(bomb.x, bomb.y);
  col = index % COLUMNS;
  line = index / COLUMNS;
  if (col < COLUMNS)
    line--;
  // retour par défaut -1
  next_index = -1;
  switch(direction)
    {
    case BOMBER_U:
      if (line - cases > 0)
	next_index = index - COLUMNS * cases; 
    case BOMBER_DOWN:
      // pour uniformiser le retour on retourne -1 mais on aurait pu tester sur < 0 à la sortie
      if (line + cases < LINES)
	next_index = index + COLUMNS * cases;
    case BOMBER_L:
      // si la colonne actuelle est inférieure aux nombre de cases souhaitées
      // pas la place donc on soustrait le nombre de case si on peut sinon return -1
      if (col >= cases)
	next_index = index - cases; 
    case BOMBER_R:
      // si la colonne de la bombe est supérieure
      // au nombre total de colonnes moins le nombre de cases
      // il n'a pas la place , donc si col est inférieure on ajoute cases
      if (col < COLUMNS - cases)
	next_index = index - cases;
    }
  return next_index;
}

// fire effect:
// wall: -1
// kill: index du joueur
// nothing: enum texture_type fire
int			check_fire_effect(t_map_destroyable case_in_fire)
{
  const SDL_Rect	sdl_target;
}

int			boom(t_map_destroyable *map_destroyable, int i)
{
  t_game_info		*game_info;
  t_map_destroyable	boom_origin;
  int			target;
  int			iterator;

  target = -1;
  game_info = get_game_info();
  boom_origin = map_destroyable[i];
  for (iterator = 1; iterator <= 3; iterator++)
    {
      // pour chaque direction on appelle une fonction capable de tester si
      // on peut avancer d'1, 2 ou 3 
      if (target = get_target(map_destroyable, bomb_origin, BOMBER_U, iterator) != -1)
	{
	  boom_origin.fire[BOMBER_U] = iterator;
	  sdl_target = init_rect
	  if (
	}
      if (target = get_target(map_destroyable, bomb_origin, BOMBER_D, iterator) != -1)
	{
	  boom_origin.fire[BOMBER_D] = iterator;
	}
      if (target = get_target(map_destroyable, bomb_origin, BOMBER_L, iterator) != -1)
	{
	  boom_origin.fire[BOMBER_L] = iterator;
	}
      if (target = get_target(map_destroyable, bomb_origin, BOMBER_R, iterator) != -1)
	{
	  boom_origin.fire[BOMBER_R] = iterator;
	}
    }
  // on sait combien de carré de feu de chaque côté
  // on tue qui de droit
  
}

