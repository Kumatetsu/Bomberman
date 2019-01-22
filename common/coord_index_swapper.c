#include <stdio.h>
#include "constant.h"

int	index_to_x(int index)
{
  return (index % COLUMNS) * PIXEL_SIZE + 144;
}

int	index_to_y(int index)
{
  int	y;

  y = index / COLUMNS;
  return (y * PIXEL_SIZE) + 96;
}

int	coord_to_index(int x, int y)
{
  int	index;
  int	col, line;

  // on trouve la colonne et la ligne, c'est tronqué
  col = x / PIXEL_SIZE - I_BEGIN;
  line = y / PIXEL_SIZE - J_BEGIN;
  // si c'est la première case
  if (col == 0 && line == 0)
    index = 0;
  // si c'est la dernière colonne
  else if (col == COLUMNS)
    // l'index est le nombre de ligne par le nombre de colonnes par ligne - 1
    index = line * COLUMNS - 1;
  // Si c'est sur la première ligne
  else if (line == 0)
    // l'index est égal à la colonne
    index = col;
  // Ce n'est pas la première ligne, ni la première case, ni la dernière case d'une ligne
  // ca peut être la première colonne
  else
    index = (line * COLUMNS + col);
  return index;
}
