/*
** my_strstr.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 18:15:00 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 11:04:45 2016 CASTELLARNAU Aurelien
*/

#include <unistd.h>

void	my_putchar(char c);
int	my_strlen(char *str);
int	my_strncmp(char *s1, char *s2, int n);

char	*my_strchr(char *str, int c)
{
  int	i;

  i = 0;
  while (*(str + i))
    {
      if (*(str + i) == c)
	return (str + i);
      ++i;
    }
  return (0);
}

char	*my_strstr(char *str, char *to_find)
{
  int	i;
  int	size_to_find;
  char	*c_stock;

  i = 0;
  size_to_find = my_strlen(to_find);
  while (*(str + i))
    {
      c_stock = my_strchr((str + i), to_find[0]);
      if (c_stock)
	{
	  if (!my_strncmp(c_stock, to_find, size_to_find))
	    {
	      return (c_stock);
	    }
	}
      ++i;
    }
  c_stock = NULL;
  return (c_stock);
}
