/*
** my_put_nbr.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour05/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Oct 22 15:42:16 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 10:57:28 2016 CASTELLARNAU Aurelien
*/

#include <unistd.h>
#include "libmy.h"

/*
int	my_nb_len(int n)
{
  int	counter;

  counter = 0;
  if (n < 0)
      n = n * -1;
  if (n == 0)
      counter = 1;
  else
    {
      while (n >= 1)
	{
	  n /= 10;
	  counter += 1;
	}
    }
  return (counter);
}
*/

void	display_exception()
{
  my_putchar('-');
  my_putchar('2');
  my_putchar('1');
  my_putchar('4');
  my_putchar('7');
  my_putchar('4');
  my_putchar('8');
  my_putchar('3');
  my_putchar('6');
  my_putchar('4');
  my_putchar('8');
}

void	manage_sign(int *n)
{
  if (*n < 0)
    {
      my_putchar('-');
      *n *= -1;
    }
}

void	my_put_nbr(int n)
{
  int	size;
  int	divisor;
  int	n_stock;

  size = my_nb_len(n) - 1;
  divisor = 1;
  if (n == -2147483648)
    display_exception();
  else
    {
      manage_sign(&n);
      while (size)
	{
	  divisor *= 10;
	  --size;
	}
      size = my_nb_len(n);
      while (size--)
	{
	  n_stock = n / divisor;
	  my_putchar(n_stock + 48);
	  n = n - n_stock * divisor;
	  divisor /= 10;
	}
    }
}
