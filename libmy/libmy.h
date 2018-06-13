/*
** libmy.h for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended/include
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Wed Feb  1 09:18:46 2017 CASTELLARNAU Aurelien
** Last update Sat Jul  1 00:26:42 2017 CASTELLARNAU Aurelien
*/

#ifndef _LIBMY_H_
# define _LIBMY_H_
# define MEM_ERR "memory allocation failed"
# define PARSE_ERROR -1
# define RUNTIME_ERROR -1
# define MANDATORY 1
# define OPTIONNAL 0
# define BUFFER 255

#include <stdio.h>
#include <stdlib.h>
/*
** typedef for t_option process
*/
typedef			void (*void_void)(void);
typedef			void (*void_char)(char *str);
typedef			void (*void_char_file)(char *str, FILE *o);
typedef			void (*void_int)(int n);
typedef			void (*void_void_star)(void*);
typedef			void (*void_int_void_star)(int nb_params, void*);
typedef			int (*int_char)(char *str);
typedef			void *(*void_star_void)(void);
typedef			void *(*void_star_void_star)(void *);
typedef			void *(*void_star_void_double_star)(void **);

/*
** structures for chainlist management
*/
typedef struct		s_link
{
  int			index;
  void			*content;
  struct s_link		*next;
  struct s_link		*prev;
}			t_link;

typedef struct		s_chain
{
  int			index;
  t_link		*first;
  t_link		*last;
  t_link		**dictionnary;
  void			(*free)(struct s_chain**);
}			t_chain;

/*
** structures used to define program arguments
*/
typedef struct		s_option
{
  int			index;
  int			mandatory;
  int			mandatory_arguments;
  int			allowed_arguments;
  int			to_execute;
  char			*name;
  void			*action;
  t_chain		*parameters;
}			t_option;

/*
** structure for logger
** level 1 (default) < ? > 3:
**   1: warning
**   2: warning, errors
**   3: ... etc
** verbose 1 (default) < ? > 3:
**   1: none
**   2: verbose simple
**   3: verbose complete
*/
typedef struct		s_logger
{
  int			lvl;
  char			*level;
  void			(*log)(const char*, char*, int);
  char			*file_path;
  char			*tic_file;
  int			tic_in_file;
}			t_logger;

/*
** libmy content
*/
void		my_putstr(const char *str);
int		my_nb_len(int nb);
void		my_putstr_color(const char *color, const char *str);
void		my_putchar(char c);
void		my_put_nbr(int nbr);
int		count_word(char *str);
void		my_put_nbr_color(const char *color, int n);
int		my_strcmp(const char *str1, const char *str2);
char		*my_strcpy(char *str, char *str_dst);
char		*my_strdup(char *str);
int		my_strlen(const char *str);
int		my_getnbr(char *str);
char		*readline(void);
int		my_isneg(int n);
char		*my_strcat(char *dest, char *src);
char		*my_strncat(char *dest, char *src, int n);
int		my_strncmp(char *s1, char *s2, int n);
char		*my_strncpy(char *dest, char *src, int n);
char		*my_strstr(char *str, char *to_find);
int		is_alpha_num(char c);
char		**my_str_to_wordtab(char *str);
void		my_swap(int *a, int *b);
char		**my_split(char *str, char separator);

/*
** display general messages from the lib
*/
int		dis_memory_fail(char *element);
int		dis_miss_arg_err(char *opt);
int		dis_mandatory_param_err(char *opt, char *param);
int		dis_mandatory_err(char *opt);
int		dis_too_much_argv(char *opt, char *excedent_arg);
int		dis_arg_err(char *opt, char *wrong_arg);

/*
** display dev shortcuts debug messages
*/
void		locate();

/*
** libParse content
*/

/*
** begin is the index to begin the parsing process, allow to avoid ./a.out
*/ 
int		parse(int begin, int argc, char *argv[], t_chain **options);
int		validate_opt(int begin, int argc, char *argv[], t_chain **options);
t_option	*new_option(int mandatory, int mandatory_arguments, int allowed_arguments, char *opt, void *action);
void		free_options_in_chain(t_chain **chain);

/*
** libList content
*/
int		init_index(t_chain **chain);
int		add_to_index(t_chain **chain, t_link **link);
int		remove_from_index(t_chain **chain, t_link *link);
t_chain		*create_chain(void (*free)(t_chain**));
int		add_link(t_chain **chain, void *content);
int		remove_link(t_chain **chain, t_link *link);
int		delete_chain(t_chain **chain);
t_link		*get_link_by_index(int index, t_chain *chain);
t_link		*get_link_by_content(void *content, t_chain *chain);
int		chain_is_null(t_chain **chain);
int		chain_is_empty(t_chain **chain);

/*
** libLog content
*/
void		log_error(char *str, FILE *o);
void		log_warning(char *str, FILE *o);
void		log_info(char *str, FILE *o);
void		log_debug(char *str, FILE *o);
void		log_tic(char *str, FILE *o);
t_logger	*build_logger(char *opt, t_chain *parameters);
t_logger	*get_logger();
void		devlog(const char *func, char *content, int lvl);
void		my_log(const char *func, char *content, int lvl);
void		delete_logger();
#endif /* !_LIBMY_H_ */
