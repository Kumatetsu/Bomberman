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
  return ((y * PIXEL_SIZE) + 96);
}

int	coord_to_index(int x, int y)
{
  int	index;
  int	col, line;

  // we find the column and the line, that's truncated
  col = x / PIXEL_SIZE - I_BEGIN;
  line = y / PIXEL_SIZE - J_BEGIN;
  // if this is the first square
  if (col == 0 && line == 0) {
    index = 0;
  }
  // if this is the last column
  else if (col == COLUMNS) {
    //the index is the number of the line by the number muliplided by the number of column less 1
    index = line * COLUMNS - 1;
  }
  // if this is on the first line
  else if (line == 0) {
    //the index is equal to the column
    index = col;
  }
  //if this is not the first line or first square or last square of a line
  // it might be the first column
  else {
    index = (line * COLUMNS + col);
  }
  return (index);
}
