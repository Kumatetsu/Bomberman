
/*
** logger.c for libmy_extended in /home/aurelien/Documents/Lib_etna/castel_a/libmy_extended/libmy
** 
** Made by CASTELLARNAU Aurelien
** Login   <castel_a@etna-alternance.net>
** 
** Started on  Tue Feb  7 23:01:39 2017 CASTELLARNAU Aurelien
** Last update Mon Apr 24 22:04:13 2017 CASTELLARNAU Aurelien
*/

#include <stdlib.h>
#include <stdio.h>
#include "libmy.h"

/*
** Call of differents level templates.
*/
const static void_char_file log_panel[] = {
  NULL,
  log_error,
  log_warning,
  log_info,
  log_debug,
  log_tic
};

/*
** General setter for log level
** Use by both default and normal logger build.
*/
int	set_level(t_logger **logger, char *level)
{
  devlog(__func__, "Try set log level to: ", 3);
  devlog(__func__, level, 3);
  if (!my_strcmp(level, "debug"))
    {
      (*logger)->lvl = 4;
      if (((*logger)->level = my_strdup("DEBUG")) == NULL)
	return (1);
    }
  else if (!my_strcmp(level, "info"))
    {
      (*logger)->lvl = 3;
      if (((*logger)->level = my_strdup("INFO")) == NULL)
	return (1);
    }
  else if (!my_strcmp(level, "warning"))
    {
      (*logger)->lvl = 2;
      if (((*logger)->level = my_strdup("WARNING")) == NULL)
	return (1);
    }
  else if (!my_strcmp(level, "error"))
    {
      (*logger)->lvl = 1;
      if (((*logger)->level = my_strdup("ERROR")) == NULL)
	return (1);
    }
  else
    return (1);
  return (0);
}

int		set_parameters(t_logger **logger, t_chain *parameters, char *opt)
{
  t_link	*ltmp;
  char		*content;

  if (!my_strcmp(opt, "-v"))
    {
      ltmp = parameters->first;
      while (ltmp)
	{
	  if ((*logger)->level == NULL
	      && set_level(logger, (char*)ltmp->content))
	    {
	      devlog(__func__, "\nlog can't be set to", 1);
	      devlog(__func__, (char*)ltmp->content, 1);
	      ltmp = parameters->last;
	    }
	  ltmp = ltmp->next;
	}
      if ((*logger)->level == NULL
	  && set_level(logger, "info"))
	devlog(__func__, "error setting log level to info", 1);
    }
  if (!my_strcmp(opt, "-log")
      && ((*logger)->file_path = my_strdup((char*)((t_link*)(parameters->dictionnary[0])->content))) == NULL)
    return (1);
  if (!my_strcmp(opt, "-ticfile"))
    {
      (*logger)->tic_in_file = 1;
      if (((*logger)->tic_file = my_strdup((char*)((t_link*)(parameters->dictionnary[0])->content))) == NULL)
	return (1);
    }
  return (0);
}


/*
** Duplicate of logger process.
** Usefull to make log before the logger is instanciate.
** Change build_default_logger to change behaviour. 
*/
t_logger		*build_default_logger()
{
  t_logger		*logger;
  
  if ((logger = malloc(sizeof(*logger))) == NULL)
    return (NULL);
  if ((logger->level = my_strdup("DEBUG")) == NULL)
    return (NULL);
  if ((logger->file_path = my_strdup("dev.log")) == NULL)
    return (NULL);
  if ((logger->tic_file = my_strdup("tic.log")) == NULL)
    return (NULL);
  logger->tic_in_file = 1;
  logger->log = my_log;
  logger->lvl = 4;
  return (logger);
}

t_logger		*get_default_logger()
{
  t_logger		*logger;
  
  if ((logger = build_default_logger()) == NULL || logger->level == NULL)
    return (NULL);
  return (logger);
}

void		devlog(const char *func, char *str, int lvl)
{
  int		file;
  t_logger	*logger;
  FILE		*o;

  file = 0;
  if ((logger = get_default_logger()) != NULL)
    {
      o = stdout;
      if (logger->file_path != NULL)
	{
	  o = fopen(logger->file_path, "a");
	  file = 1;
	}
      if (lvl == 5
	  && logger->tic_in_file
	  && logger->tic_file != NULL)
	{
	  o = fopen(logger->tic_file, "a");
	  log_tic(str, o);
	  fclose(o);
	}
      else if (lvl <= logger->lvl ||
	       (lvl == 5 && logger->tic_in_file == 0))
	{
	  fprintf(o, "\n[CS/");
	  fprintf(o, func);
	  fprintf(o, "] ");
	  log_panel[lvl](str, o);
	}
      fclose(o);
      free(logger->file_path);
      free(logger->level);
      free(logger);
    }
}
/*
** End of dev_log() functions set.
*/

void		my_log(const char *func, char *str, int lvl)
{
  int		file;
  t_logger	*logger;
  FILE		*o;
  FILE		*tic_o;
  
  file = 0;
  if ((logger = get_logger()) != NULL)
    {
      o = stdout;
      tic_o = stdout;
      if (logger->file_path != NULL)
	{
	  o = fopen(logger->file_path, "a");
	  file = 1;
	}
      if (lvl == 5
	  && logger->tic_in_file == 1
	  && logger->tic_file != NULL)
	{
	  tic_o = fopen(logger->tic_file, "a");
	  log_tic(str, tic_o);
	  fclose(tic_o);
	}
      else if (lvl <= logger->lvl ||
	       (lvl == 5 && logger->tic_in_file == 0))
	{
	  fprintf(o, "\n[CS/");
	  fprintf(o, func);
	  fprintf(o, "] ");
	  log_panel[lvl](str, o);
	}
      if (file)
	fclose(o);
    }
}

t_logger		*build_logger(char *opt, t_chain *parameters)
{
  static t_logger	*logger;

  if (logger == NULL)
    {
      if ((logger = malloc(sizeof(*logger))) == NULL)
	return (NULL);
      logger->log = my_log;
      logger->level = NULL;
      logger->file_path = NULL;
      logger->tic_file = NULL;
      logger->tic_in_file = 0;
      if (opt == NULL)
	{
	  if ((logger->level = my_strdup("ERROR")) == NULL)
	    return (NULL);
	  if ((logger->file_path = my_strdup("error.log")) == NULL)
	    return (NULL);
	  if ((logger->tic_file = my_strdup("ticker.log")) == NULL)
	    return (NULL);
	  logger->lvl = 1;
	  logger->tic_in_file = 1;
	}
      }
  if (opt != NULL)
    {
      char log [50];
      sprintf(log, "set option %s", opt);
      devlog(__func__, log, 4);
      if (set_parameters(&logger, parameters, opt))
	return (NULL);
    }
  return (logger);
}

t_logger		*get_logger()
{
  t_logger		*logger;
  
  if ((logger = build_logger(NULL, NULL)) == NULL || logger->level == NULL)
    return (NULL);
  return (logger);
}

void		delete_logger()
{
  t_logger	*logger;

  if ((logger = get_logger()) != NULL)
    {
      if (logger->level != NULL)
	free(logger->level);
      if (logger->file_path != NULL)
	free(logger->file_path);
      if (logger->tic_file != NULL)
	free(logger->tic_file);
      free(logger);
    }
}
