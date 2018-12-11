##
## Makefile for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
##
## Made by MASERA Mathieu
## Login   <masera_m@etna-alternance.net>
##
## Started on  Wed Jul  4 09:36:47 2018 MASERA Mathieu
## Last update Wed Jul  4 09:36:48 2018 MASERA Mathieu
##

CC 	= gcc

NAME 	= BomberMan

#-W -Werror -Wextra -Wall
CFLAGS 	= -g -Iincludes/ -Ilibmy

LDFLAGS =  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -pthread -L ./libmy

SRC 	= 	main.c 					\
		menu.c					\
		common/game_info_serialization.c	\
		common/request_serialization.c		\
		common/my_putchar.c			\
		common/my_putstr.c			\
		common/game_info.c			\
		common/utils_map.c			\
		start_map.c				\
		game_map/white_bomber.c			\
		game_map/blue_bomber.c			\
		game_map/red_bomber.c			\
		game_map/black_bomber.c			\
		game_map/bomb.c				\
	 	sdl/init.c 				\
		client/client.c 			\
		client/socket.c				\
		client/client_request.c			\
		client/client_get_game_info.c		\
		client/client_socket_thread.c\
		server/server.c				\
		server/thread.c				\
		server/bomb_management.c		\
		server/map_management.c			\
		server/moving.c				\
		server/request_handling.c		\
                server/player.c			\
		server/main_loop.c			\
		base_map/base_map_manager.c		\
		base_map/draw_base_map.c		\
		base_map/init_tools.c			\
		base_map/draw_players.c			\
		game_event.c				\

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
