/*
** my_putstr.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Oct 20 17:11:35 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 10:57:48 2016 CASTELLARNAU Aurelien
*/

void	my_putchar(char c);

void	my_putstr(char *str)
{
  while (*str != '\0')
    {
      my_putchar(*str);
      ++str;
    }
}
