/*
** my_strcmp.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 11:59:53 2016 CASTELLARNAU Aurelien
** Last update Mon Apr 17 20:55:01 2017 CASTELLARNAU Aurelien
*/

int	my_strcmp(const char *s1, const char *s2)
{
  int	i;

  i = 0;
  while (*(s1 + i) != '\0' || *(s2 + i) != '\0')
    {
      if (*(s1 + i) != *(s2 + i))
	{
	  if (s1[i] > s2[i])
	    return (1);
	  else if (s1[i] < s2[i])
	    return (-1);
	  else
	    return (0);
	}
      ++i;
    }
  return (0);
}
