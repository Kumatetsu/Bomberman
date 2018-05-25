
CC 	= gcc

NAME 	= BomberMan

CFLAGS 	= -W -Werror -Wextra -Wall -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

SRC 	= main.c

OBJ 	= ${SRC:%.c=%.o}

RM 	= rm -rf

all 	: ${NAME}

re 	: clean all

$(NAME) : $(OBJ)
	  $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean	:
	  $(RM) $(OBJ)

fclean 	: clean
	  $(RM) $(NAME)

.PHONY	: all clean fclean