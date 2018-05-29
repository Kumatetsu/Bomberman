
CC 	= gcc

NAME 	= BomberMan

CFLAGS 	= -W -Werror -Wextra -Wall -g -Iincludes/ -Ilibmy

LDFLAGS =  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -L ./libmy

SRC 	= 	main.c 			\
	 	views/init.c 		\
		loops/client_sdl_loop.c \
		loops/menu_sdl_loop.c	\

OBJ 	= ${SRC:%.c=%.o}

RM 	= rm -rf

all 	: ${NAME}

re 	: clean all

$(NAME) : $(OBJ)
	  $(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean	:
	  $(RM) $(OBJ)

fclean 	: clean
	  $(RM) $(NAME)

.PHONY	: all clean fclean