/*
** Ce fichier contient les fonctions de bases pour gérer des strings (les chaines de caractères).
**
** my_putchar vous permet d'afficher un caractère sour la sortie standard.
** 
** my_strlen renvoie la taille d'une string.
**
** my_putstr vous permet d'afficher une string sur la sortie standard.
**
** my_strcmp vous permet de comparer deux strings si ces strings sont égales alors
** la fonction renvoie 0.
**
** my_strdup vous permet d'allouer dynamiquement une chaine de caractères et de copier la valeur de
** la chaine passé en paramètre et de renvoyer cette chaine.
**
** my_putstr_color vous permet d'afficher une string sur la sortie standard de la couleur souhaitée.
** les couleurs disponibles pour cette fonction sont rouge (red), vert (green), jaune (yellow),
** bleu (blue), violet (magenta), et bleu cyan (cyan), elle vous permet également d'effacer
** tout ce qui est actuellement affiché à l'écran (clear) avant d'afficher votre chaine de caractères.
*/

#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"

#ifndef			_COLOR_
# define		_COLOR_

const char		*reset_color = "\033[0m";

typedef			struct s_color	t_color;

struct			s_color
{
  char			*color;
  char			*unicode;
};

static const t_color	g_color[] =
  {
    {"clear", "\033[H\033[2J"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"here_new", "http://misc.flogisoft.com/bash/tip_colors_and_formatting"},
    {NULL, NULL}
  };

#endif			/* !_COLOR_ */

void	my_putstr_color(const char *color, const char *str)
{
  int	i;

  i = 0;
  while (g_color[i].color != NULL && (my_strcmp(g_color[i].color, color) != 0))
    i++;
  if (g_color[i].color == NULL)
    {
      my_putstr(str);
      return ;
    }
  my_putstr(g_color[i].unicode);
  my_putstr(str);
  my_putstr(reset_color);
}

void	display_exception_color()
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

void	manage_sign_color(int *n)
{
  if (*n < 0)
    {
      my_putchar('-');
      *n *= -1;
    }
}

void	get_color(const char *color)
{
  int	i;

  i = 0;
  while (g_color[i].color != NULL && (my_strcmp(g_color[i].color, color) != 0))
    i++;
  if (g_color[i].color == NULL)
    {
      my_putstr(reset_color);
      return ;
    }
  my_putstr(g_color[i].unicode);
}

void	my_put_nbr_color(const char *color, int n)
{
  int	size;
  int	divisor;
  int	n_stock;

  get_color(color);
  size = my_nb_len(n) - 1;
  divisor = 1;
  if (n == -2147483648)
    display_exception_color();
  else
    {
      manage_sign_color(&n);
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
  my_putstr(reset_color);
}
