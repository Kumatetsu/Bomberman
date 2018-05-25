/*
** my_strlen.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Oct 20 17:12:26 2016 CASTELLARNAU Aurelien
** Last update Mon Apr 17 20:53:50 2017 CASTELLARNAU Aurelien
*/

int	my_strlen(const char *str)
{
  int	i;

  i = 0;
  while (*str != '\0')
    {
      ++i;
      ++str;
    }
  return (i);
}
