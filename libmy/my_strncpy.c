/*
** my_strncpy.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 11:47:04 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 11:03:54 2016 CASTELLARNAU Aurelien
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	i;
  int	check;

  i = 0;
  check = 0;
  while (i < n)
    {
      if (*(src + i) == '\0')
	check = 1;
      if (check)
	dest[i] = 0;
      else
	dest[i] = *(src + i);
      ++i;
    }
  return (dest);
}
