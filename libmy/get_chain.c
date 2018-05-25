/*
** get_chain.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended/libmy
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Feb  3 03:48:12 2017 CASTELLARNAU Aurelien
** Last update Fri Feb 10 15:36:39 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

/*
** useless function from step 1 of liblist.
*/
t_link	*get_link_by_index(int index, t_chain *chain)
{
  return (chain->dictionnary[index]);
}

/*
** function allow user to get a link by comparing
** the void* content.
*/
t_link	*get_link_by_content(void *content, t_chain *chain)
{
  int	iter;

  iter = chain->first->index;
  while (iter < chain->index)
    {
      if (content ==  chain->dictionnary[iter]->content)
	return (chain->dictionnary[iter]);
      ++iter;
    }
  return (NULL);
}
