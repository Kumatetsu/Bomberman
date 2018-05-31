/*
** display_general_err.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Feb  8 13:27:04 2017 CASTELLARNAU Aurelien
** Last update Mon Feb 13 21:52:07 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

/*
** Display library error message
*/

int     dis_miss_arg_err(char *opt)
{
  my_putstr("\nMissing parameter for option: ");
  my_putstr(opt);
  my_putstr("\n");
  return (1);
}

int     dis_mandatory_err(char *opt)
{
  my_putstr("\n The mandatory option: ");
  my_putstr(opt);
  my_putstr(" isn\'t present or valid.\n");
  return (1);
}

int	dis_mandatory_param_err(char *opt, char *param)
{
  my_putstr("\nThe mandatory parameter: ");
  my_putstr(param);
  my_putstr(" for option ");
  my_putstr(opt);
  my_putstr("\n isn't present or valid\n");
  return (1);
}

int	dis_too_much_argv(char *opt, char *exedent_arg)
{
  my_putstr("\nToo much argument for option ");
  my_putstr(opt);
  my_putstr("\nThe program can't deal with the argument: ");
  my_putstr(exedent_arg);
  my_putstr("\n");
  return (1);
}

int	dis_arg_err(char *opt, char *wrong_arg)
{
  my_putstr("\n Wrong argument: ");
  my_putstr(wrong_arg);
  my_putstr(" for option.");
  my_putstr(opt);
  my_putstr("\n");
  return (1);
}

int	dis_memory_fail(char *element)
{
  my_putstr("\nCRITICAL ERR\n");
  my_putstr("Not enought memory to allocate: ");
  my_putstr(element);
  return (1);
}
