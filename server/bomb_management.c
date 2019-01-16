#include "constant.h"
#include "map.h"
#include "game_info.h"

int			boom(t_map_destroyable *map_destroyable, int i)
{
  t_game_info		*game_info;
  t_map_destroyable	boom_origin;
  // les cases concernées par l'explosion
  t_map_destroyable	boom_cases[13];
  int			iterator;
  int			x, y;
  int			x_case, y_case;
  
  game_info = get_game_info();
  boom_origin = map_destroyable[i];
  x = boom_origin.x;
  y = boom_origin.y;
  // attribution des cases à gauche du point d'origin
  // doit être sur le même y mais x doit varier en restant dans la map
  // on part de la case i et on se déplace vers la gauche
  for (iterator = i; iterator >= (i - 3); iterator--)
    {
      // la bombe est sur la première ligne, y_case == 0
      if (i < 15)
	{
	  y_case = 0;
	  x_case = PIXEL_SIZE * i;
	}
      else
	{
	  y_case = (i / COLUMNS) * PIXEL_SIZE;
	  x_case = (i % COLUMNS) * PIXEL_SIZE;
	}
      // on a désormais x et y de la case d'origine sur notre INLINE_MATRIX
      // si le reste de la division de i par le nombre de colonnes est inférieure à 3
      else if (i % COLUMNS < 3)
	{
	  // on ne dispose pas de 3 cases sur la gauche.
      	}
      // si le reste de la division de i par le nombre de colonnes est supérieur à 10
      else if (i % COLUMNS > 10)
	{
	  // on ne dispose pas de 3 cases sur la droite
	}
      if (iterator
    }
}
