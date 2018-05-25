/*
** create_list.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended/libmy
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Feb  3 02:13:19 2017 CASTELLARNAU Aurelien
** Last update Thu Apr 27 22:21:29 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

t_chain		*create_chain(void (*free)(t_chain**))
{
  t_chain	*chain;

  if ((chain = malloc(sizeof(*chain))) == NULL)
    {
      devlog(__func__, MEM_ERR, 1);
      return (NULL);
    }
  chain->first = NULL;
  chain->last = NULL;
  chain->index = 0;
  chain->dictionnary = NULL;
  chain->free = free;
  return (chain);
}

void	init_chain(t_chain **chain, t_link **link)
{
  (*chain)->first = (*link);
  (*chain)->last = (*link);
  (*link)->next = NULL;
  (*link)->prev = NULL;
}

int		add_link(t_chain **chain, void *content)
{
  t_link	*link;

  if ((link = malloc(sizeof(*link))) == NULL)
    {
      devlog(__func__, MEM_ERR, 1);
      return (1);
    }
  link->content = content;
  if (chain_is_empty(chain))
    {
      init_chain(chain, &link);
      init_index(chain);
    }
  else
    {
      (*chain)->last->next = link;
      link->next = NULL;
      link->prev = (*chain)->last;
      (*chain)->last = link;
      add_to_index(chain, &link);
    }
  (*chain)->index++;
  return (0);
}

int		remove_link(t_chain **chain, t_link *link)
{
  if (link == (*chain)->first && link == (*chain)->last)
    {
      (*chain)->first = NULL;
      (*chain)->last = NULL;
      free(link);
      return (-1);
    }
  else if (link == (*chain)->first)
    {
      (*chain)->first->next->prev = NULL;
      (*chain)->first = (*chain)->first->next;
    }
  else if (link == (*chain)->last)
    {
      (*chain)->last->prev->next = NULL;
      (*chain)->last = (*chain)->last->prev;
    }
  else
    {
      link->next->prev = link->prev;
      link->prev->next = link->next;
    }
  if ((*chain) != NULL)
    {
      if (remove_from_index(chain, link))
	{
	  devlog(__func__, "can't remove link from index", 1);
	  return (1);
	}
      (*chain)->index--;
    }
  free(link);
  return (0);
}

int	delete_chain(t_chain **chain)
{
  if ((*chain)->free != NULL)
    (*chain)->free(chain);
  while ((*chain)->first != NULL)
    {
      if (remove_link(chain, (*chain)->last))
	return (1);
    }
  free((*chain)->dictionnary);
  free((*chain));
  return (0);
}

int	chain_is_null(t_chain **chain)
{
  if (chain == NULL ||
      (*chain) == NULL)
    return (1);
  return (0);
}

int	chain_is_empty(t_chain **chain)
{
  if (chain == NULL ||
      (*chain) == NULL ||
      (*chain)->first == NULL)
    return (1);
  return (0);
}
