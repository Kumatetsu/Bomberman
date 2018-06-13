/*
** indexor.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Feb  3 03:21:04 2017 CASTELLARNAU Aurelien
** Last update Mon Apr 10 21:19:18 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

int	init_index(t_chain **chain)
{
  if (((*chain)->dictionnary = malloc(sizeof(*((*chain)->first)))) == NULL)
    return (1);
  (*chain)->dictionnary[(*chain)->index] = (*chain)->first;
  (*chain)->first->index = (*chain)->index;
  (*chain)->index = 0;
  return (0);
}

int		add_to_index(t_chain **chain, t_link **link)
{
  int		index;
  t_link	**tmp;
  t_link	*ltmp;
  t_option	*otmp;
  
  index = (*chain)->first->index;
  if ((tmp = malloc((1 + (*chain)->index) * sizeof(t_link))) == NULL)
    return (1);
  while (index < (*chain)->index)
    {
      tmp[index] = (*chain)->dictionnary[index];
      tmp[index]->index = index;
      ++index;
    }
  (*link)->index = (*chain)->index;
  tmp[(*chain)->index] = (*link);
  free((*chain)->dictionnary);
  (*chain)->dictionnary = NULL;
  (*chain)->dictionnary = tmp;
  return (0);
}

int		remove_from_index(t_chain **chain, t_link *link)
{
  int		index;
  t_link	**tmp;

  tmp = NULL;
  if ((tmp = malloc(((*chain)->index) *  sizeof(*link))) == NULL)
    return (1);
  index = 0;
  while (link != NULL && index < link->index)
    {
      tmp[index] = (*chain)->dictionnary[index];
      ++index;
    }
  while (index + 1 < (*chain)->index)
    {
      tmp[index] = (*chain)->dictionnary[index + 1];
      tmp[index]->index = index;
      ++index;
    }
  free((*chain)->dictionnary);
  (*chain)->dictionnary = NULL;
  (*chain)->dictionnary = tmp;
  return (0);
}
