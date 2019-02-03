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
## -W -Werror -Wextra -Wall
CFLAGS 	= -g -Iincludes/ -Ilibmy

LDFLAGS =  -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -pthread -L ./libmy

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
		client/client_interpretor.c 	\
		client/update_client.c\
		server/server.c				\
		server/thread.c				\
		server/map_management.c			\
		server/moving.c				\
		server/bomb.c		\
        server/player.c				\
		server/main_loop.c			\
		server/collision.c			\
		server/bomb_management.c		\
		server/notify_client.c			\
		server/command_interpretor.c    \
		base_map/base_map_manager.c		\
		base_map/draw_base_map.c		\
		base_map/draw_players.c			\
		devtools/detail_game_info.c		\

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
