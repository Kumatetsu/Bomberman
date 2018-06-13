
CC 	= gcc

NAME 	= BomberMan

CFLAGS 	= -W -Werror -Wextra -Wall -g -Iincludes/ -Ilibmy

LDFLAGS =  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -pthread -L ./libmy

SRC 	= 	main.c 				\
		menu.c				\
		start_map.c			\
		white_bomber.c			\
	 	sdl/init.c 			\
		client/client.c 		\
		client/socket.c			\
		server/server.c			\
		server/socket.c			\
		server/create_server.c		\
		server/thread.c			\
		server/player.c			\
		base_map/base_map_manager.c	\
		base_map/draw_base_map.c		\
		base_map/init_tools.c		\

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
