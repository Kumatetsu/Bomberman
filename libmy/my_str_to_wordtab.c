/*
** my_str_to_wordtab.c for libmy_finale in /home/aurelien/repertoire_rendu/piscine_C/Jour07/castel_a
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Mon Oct 24 14:47:39 2016 CASTELLARNAU Aurelien
** Last update Mon Apr 24 23:50:39 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include "libmy.h"

int	is_alpha_num(char c)
{
  if ((c >= '0' && c <= '9')
      || (c >= 'A' && c <= 'Z')
      || (c >= 'a' && c <= 'z')
      || c == '-')
    return (1);
  else
    return (0);
}

int	count_word(char *str)
{
  int	i;
  int	mots;

  i = 0;
  mots = 0;
  while (*(str + i))
    {
      while (!is_alpha_num(*(str + i)))
	++i;
      while (is_alpha_num(*(str + i)))
	++i;
      ++mots;
    }
  return (mots);
}

char	*organize_tab(char *str, int *i, int *stock_i)
{
  int	word_size;
  char	*temp_str;

  word_size = 0;
  while (!is_alpha_num(*(str + *i)))
    ++(*i);
  while (is_alpha_num(*(str + *i)))
    {
      ++(*i);
      ++word_size;
    }
  *stock_i = *i;
  if ((temp_str = malloc(sizeof (str[0]) * word_size + 1)) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  temp_str[word_size] = '\0';
  while (word_size)
    {
      --word_size;
      --(*i);
      temp_str[word_size] = str[*i];
    }
  return (temp_str);
}

char	**my_str_to_wordtab(char *str)
{
  int	i;
  int	k;
  int	stock_i;
  int	word_counter;
  char	*temp_str;
  char	**wordtab;

  i = 0;
  k = 0;
  word_counter = count_word(str);
  if ((wordtab = malloc(sizeof (str) * word_counter + 1)) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  while (k < word_counter)
    {
      if ((temp_str = organize_tab(str, &i, &stock_i)) == NULL)
	return (NULL);
      if ((wordtab[k] = my_strdup(temp_str)) == NULL)
	return (NULL);
      free(temp_str);
      i = stock_i;
      ++k;
    }
  return (wordtab);
}

