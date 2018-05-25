/*
** my_swap.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Thu Oct 20 17:12:46 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 11:06:17 2016 CASTELLARNAU Aurelien
*/

void	my_swap(int *a, int *b)
{
  int	a_value;

  a_value = *a;
  *a = *b;
  *b = a_value;
}
