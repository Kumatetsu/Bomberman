/*
** readline.c for my_FTL in /home/aurelien/aurelien/ftl/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Nov 11 15:36:20 2016 CASTELLARNAU Aurelien
** Last update Wed Apr 26 10:27:38 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include <unistd.h>

/*
** Cette fonction permet de récuper une ligne
** de moins de 50 caractères sur l'entrée standard.
** La fonction ne prend pas de paramètre et renvoit une chaîne
** allouée (pensez a free()).
*/
char		*readline(void)
{
  ssize_t	ret;
  char		*buff;

  if ((buff = malloc((1024 + 1) * sizeof(char))) == NULL)
    return (NULL);
  if ((ret = read(0, buff, 1025)) > 0)
    {
      buff[ret - 1] = '\0';
      return (buff);
    }
  if (ret < 0)
    devlog(__func__, "readline return -1", 1);
  free(buff);
  return (NULL);
}
