#include <stdlib.h>

t_chain*create_chain(void (*free)(t_chain**))
{
  t_chain*chain;

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

voidinit_chain(t_chain **chain, t_link **link)
{
  (*chain)->first = (*link);
  (*chain)->last = (*link);
  (*link)->next = NULL;
  (*link)->prev = NULL;
}

intadd_link(t_chain **chain, void *content)
{
  t_link*link;

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

intremove_link(t_chain **chain, t_link *link)
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

intdelete_chain(t_chain **chain)
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

intchain_is_null(t_chain **chain)
{
  if (chain == NULL ||
      (*chain) == NULL)
    return (1);
  return (0);
}

intchain_is_empty(t_chain **chain)
{
  if (chain == NULL ||
      (*chain) == NULL ||
      (*chain)->first == NULL)
    return (1);
  return (0);
}
