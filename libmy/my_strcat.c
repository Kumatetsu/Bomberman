/*
** my_strcat.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 12:49:49 2016 CASTELLARNAU Aurelien
** Last update Mon Apr 24 23:20:52 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

char	*my_strcat(char *dest, char *src)
{
  int	i;
  int	j;
  char	*cat;

  i = 0;
  j = 0;
  while (*(dest + i) != '\0')
    ++i;
  while (*(src + j) != '\0')
    ++j;
  if ((cat = malloc(sizeof(char) * (j + i + 1))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  i = 0;
  while (*(dest + i) != '\0')
    {
      cat[i] = dest[i];
      ++i;
    }
  j = 0;
  while (*(src + j) != '\0')
    {
      cat[i] = src[j];
      ++i;
      ++j;
    }
  cat[i] = '\0';
  return (&cat[0]);
}
