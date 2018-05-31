/*
** log_panel.c for libmy_extended in /home/aurelien/Documents/demoLib/demoParse/libmy
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Apr 12 23:35:39 2017 CASTELLARNAU Aurelien
** Last update Mon Apr 17 21:07:41 2017 CASTELLARNAU Aurelien
*/

#include <stdio.h>
#include <time.h>
#include "libmy.h"
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
/*
** https://stackoverflow.com/questions/1442116/how-to-get-date-and-time-value-in-c-program
*/
void	print_time(FILE *o)
{
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char s[64];
  strftime(s, sizeof(s), "%c", tm);
  fprintf(o, "%s ", s);
}

void    log_error(char *str, FILE *o)
{
  print_time(o);
  fprintf(o, "%s< ERROR >%s", RED, NRM);
  fprintf(o, str);
}

void    log_warning(char *str, FILE *o)
{
  print_time(o);
  fprintf(o, "%s< WARNING >%s ", YEL, NRM);
  fprintf(o, str);
}

void    log_info(char *str, FILE *o)
{
  print_time(o);
  fprintf(o, "%s< INFO >%s ", BLU, NRM);
  fprintf(o, str);
}

void    log_debug(char *str, FILE *o)
{
  print_time(o);
  fprintf(o, "%s< DEBUG >%s ", GRN, NRM);
  fprintf(o, str);
}

void    log_tic(char *str, FILE *o)
{
  fprintf(o, "\n");
  print_time(o);
  fprintf(o, "<GAME-INFO>");
  fprintf(o, str);
}
