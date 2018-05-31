/*
** my_getnbr.c for libmy.a in /home/aurelien/repertoire_rendu/piscine_C/libmy01/castel_a/libmy_02
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Tue Oct 25 13:28:09 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 10:51:29 2016 CASTELLARNAU Aurelien
*/

#include <stdio.h>

void	my_putchar(char c);
void	my_put_nbr(int i);
void	my_putstr(char *str);

int	pow_ten(char *src, int i, int pos_int)
{
  int	ten_pow;
  int	elmt;

  ten_pow = 1;
  elmt = 0;
  while (pos_int > 1)
    {
      ten_pow *= 10;
      --pos_int;
    }
  elmt = (*(src + i) - 48) * ten_pow;
  return (elmt);
}

void	get_size_and_sign(char *str,int *i, int *sign, int *nbr_len)
{
  while (*(str + *i) == 45 || *(str + *i) == 43)
    {
      if (*(str + *i) == 45)
	*sign *= -1; 
      ++*i;
    }
  while (*(str + *i) >= '0' && *(str + *i) <= '9')
    {
      *nbr_len = *nbr_len + 1;
      ++*i;
    }
}

int	my_getnbr(char *str)
{
  int	i;
  int	pos_int;
  int	nbr_len;
  int	nbr_index;
  int	sign;
  int	the_int;

  i = 0;
  sign = 1;
  pos_int = 1;
  nbr_len = 0;
  the_int = 0;
  get_size_and_sign(str, &i, &sign, &nbr_len);
  nbr_index = i - nbr_len;
  --i;
  while (i >= nbr_index)
    {
      the_int += pow_ten(str, i, pos_int);
      --i;
      ++pos_int;
    }
  the_int *= sign;
  return (the_int);
}
