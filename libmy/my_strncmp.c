/*
** my_strncmp.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 12:35:49 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 11:02:48 2016 CASTELLARNAU Aurelien
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  while (i < n && (*(s1 + i) != '\0' || *(s2 + i) != '\0'))
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
