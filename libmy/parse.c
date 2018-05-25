/*
** parse.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended/LibParse
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Feb  1 13:14:04 2017 CASTELLARNAU Aurelien
** Last update Mon Apr 24 23:46:46 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

/*
** Function use to call validation
** and organisation of the arguments
** if all tests pass, parse() reorganize
** t_chain **options and return success/error.
*/
int		parse(int begin,
		      int argc,
		      char *argv[],
		      t_chain **options)
{
  int		check;
  
  check = validate_opt(begin, argc, argv, options);
  if (check)
    my_log(__func__, "error on parsing arguments", 1);
  return (check);
}
