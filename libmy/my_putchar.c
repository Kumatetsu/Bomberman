/*
** my_putchar.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Sat Oct 22 19:56:34 2016 CASTELLARNAU Aurelien
** Last update Wed Nov 16 10:56:29 2016 CASTELLARNAU Aurelien
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

