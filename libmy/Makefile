##
## Makefile for libmy in /home/aurelien/repertoire_rendu/piscine_C/libmy01/castel_a
## 
## Made by CASTELLARNAU Aurelien
## Login   <castel_a@etna-alternance.net>
## 
## Started on  Sat Oct 22 20:51:03 2016 CASTELLARNAU Aurelien
## Last update Mon Apr 24 22:08:28 2017 CASTELLARNAU Aurelien
##

CC	=	gcc

NAME	=	libmy.a	

SRC	=	my_putchar.c \
		my_isneg.c \
		my_nb_len.c \
		my_put_nbr.c \
		my_swap.c \
		my_putstr.c \
		my_strlen.c \
		my_getnbr.c \
		my_strcpy.c \
		my_strncpy.c \
		my_strcmp.c \
		my_strncmp.c \
		my_strcat.c \
		my_strncat.c \
		my_strstr.c \
		my_str_to_wordtab.c \
		my_split.c \
		my_strdup.c \
		my_string.c \
		readline.c \
		internal_debug.c \
		display_general_err.c \
		options_manager.c \
		validate_opt.c \
		parse.c \
		indexor.c \
		chain_manager.c \
		get_chain.c \
		log_panel.c \
		logger.c

OBJ	=	$(SRC:%.c=%.o)

RM	=	rm	-f

$(NAME)	:	$(OBJ)
		ar	rc	$(NAME)	$(OBJ)
		ranlib	$(NAME)

all	:	$(NAME)

clean	:
		$(RM)	$(OBJ)

fclean	:	clean
		$(RM)	$(NAME)

re	:	clean	all

.PHONY	:	all	clean	fclean
