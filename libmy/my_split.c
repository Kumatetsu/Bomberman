/*
** my_split.c for libmy extended in 
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Fri Jul 14 23:12:59 2017 CASTELLARNAU Aurelien
** Last update Fri Jul 14 23:38:01 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include <stdio.h>
#include "libmy.h"

int     count_split(char *str, char separator)
{
  int   i;
  int   words;

  i = 0;
  words = 0;
  while (*(str + i) == separator)
    ++i;
  while (*(str + i))
    {
      while (*(str + i) && *(str + i) != separator)
	++i;
      ++words;
      if (*(str + i) == separator && *(str + i))
	++i;
    }
  return (words);
}

char	*extract_word(char **str, char separator, int *cursor)
{
  int	it;
  int	part_size;
  int	save_cursor;
  char	*part;
  char *tmp;

  it = 0;
  part_size = 0;
  while ((*str)[*cursor] == separator)
    ++(*cursor);
  save_cursor = *cursor;
  while (*((*str) + *cursor) && *((*str) + *cursor) != separator)
    {
      ++(*cursor);
      ++part_size;
    }
  if ((part = malloc(sizeof ((*str)) * part_size + 1)) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  *cursor = save_cursor;
  while (it < part_size && (*str)[*cursor] != separator)
    {
      part[it] = (*str)[*cursor];
      ++(*cursor);
      ++it;
    }
  part[part_size] = '\0';
  return (part);
}

char	**my_split(char *str, char separator)
{
  char	*split_part;
  char	**splitted;
  int	word_counter;
  int	it;
  int	cursor;

  word_counter = count_split(str, separator);
  it = 0;
  while (*(str + it) == separator)
    ++it;
  cursor = it;
  if ((splitted = malloc(sizeof (*splitted) * (word_counter + 1))) == NULL)
    {
      my_log(__func__, MEM_ERR, 1);
      return (NULL);
    }
  *(splitted + word_counter) = NULL;
  it = 0;
  while (it < word_counter)
    {
      if ((split_part = extract_word(&str, separator, &cursor)) == NULL)
	return (NULL);
      if ((splitted[it] = my_strdup(split_part)) == NULL)
	return (NULL);
      ++it;
    }
  return (splitted);
}
