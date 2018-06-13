/*
** my_nb_len.c for libmy_extended in /home/aurelien/Documents/my_slack/depot/castel_a/client_my_slack
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Mon Apr 24 22:07:01 2017 CASTELLARNAU Aurelien
** Last update Mon Apr 24 22:08:11 2017 CASTELLARNAU Aurelien
*/

#include "libmy.h"

int     my_nb_len(int n)
{
  int   counter;

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
