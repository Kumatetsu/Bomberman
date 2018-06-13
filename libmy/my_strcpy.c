/*
** my_strcpy.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour04/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 11:19:52 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 10:59:21 2016 CASTELLARNAU Aurelien
*/

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (*(src + i) != '\0')
    {
      dest[i] = *(src + i);
      ++i;
    }
  dest[i] = '\0';
  return (dest);
}
