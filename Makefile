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

CFLAGS 	= -W -Werror -Wextra -Wall -g -Iincludes/ -Ilibmy

LDFLAGS = -lmingw32 -mwindows -lpthread -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -pthread -lws2_32 -L ./libmy -L/opt/local/i686-w64-mingw32/lib

SRC 	= 	main.c 					\
		menu.c					\
	 	start_map.c				\
		sdl.c	 				\
		common/game_info_serialization.c	\
		common/request_serialization.c		\
		common/my_putchar.c			\
		common/my_putstr.c			\
		common/game_info.c			\
		common/static_wall_rect.c 		\
		common/coord_index_swapper.c		\
		game_map/white_bomber.c			\
		game_map/blue_bomber.c			\
		game_map/red_bomber.c			\
		game_map/black_bomber.c			\
		game_map/bomb.c				\
		client/client.c 			\
		client/client_request.c			\
		client/client_receive.c			\
		client/bomber_sprites.c			\
		server/server.c				\
		server/thread.c				\
		server/map_management.c			\
		server/moving.c				\
		server/request_handling.c		\
                server/player.c				\
		server/main_loop.c			\
		server/collision.c			\
		server/bomb_management.c		\
		base_map/base_map_manager.c		\
		base_map/draw_base_map.c		\
		base_map/draw_players.c			\
		devtools/detail_game_info.c		\
		devtools/windows_nanosleep.c    \

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
