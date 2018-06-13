/*
** my_strdup.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour07/castel_a/my_strdup
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Mon Oct 24 14:04:57 2016 CASTELLARNAU Aurelien
** Last update Thu Feb  2 22:37:31 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

char	*my_strcpy(char *dest, char *src);

char	*my_strdup(char *str)
{
  char	*str2;
  int	i;

  i = 0;
  if (str == NULL)
    {
      devlog(__func__, "try to strdup a NULL value", 3);
      return (NULL);
    }
  while (*(str + i))
    ++i;
  if ((str2 = malloc(sizeof(*str) * i + 1)) == NULL)
    {
      devlog(__func__, MEM_ERR, 1);
      return (NULL);
    }
  if (str2 != 0)
    {
      my_strcpy(str2, str);
      return (str2);
    }
}
