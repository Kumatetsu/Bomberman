
CC 	= gcc

CFLAGS 	= -W -Werror -Wextra -Wall -pedantic -g -Iinclude/

LDFLAGS = -pthread

CLI_SRC =	client/client.c	\
		client/create_cli_socket.c	\
		client/client_loop.c	\
		client/client_request.c	\
		common/request_communication.c	\
		common/my_putchar.c \
		common/my_putstr.c \
		common/game_info_serialization.c \
		server/game_info.c \

SRV_SRC =	server/server.c	\
		server/thread.c \
		server/game_info.c \
		server/create_srv_socket.c	\
		server/create_srv_struct.c	\
		server/srv_actions.c	\
		server/main_loop.c	\
		server/moving.c      		    \
		server/map_management.c 	    \
		server/bomb_management.c 	    \
		common/request_communication.c	\
		common/game_info_serialization.c \
		common/my_putchar.c	\
		common/my_putstr.c	\

CLI_OBJ = ${CLI_SRC:%.c=%.o}

SRV_OBJ = ${SRV_SRC:%.c=%.o}

RM 	= rm -rf

all: cli serv

re 	: clean all

cli	:	$(CLI_OBJ)
		$(CC) $(CFLAGS)		$(CLI_OBJ)	$(LDFLAGS) 	-o	cli

serv :	$(SRV_OBJ)
		$(CC) $(CFLAGS)		$(SRV_OBJ)	$(LDFLAGS)	-o	serv

clean :
	  $(RM) $(CLI_OBJ) $(SRV_OBJ)

fclean 	: clean
	  $(RM) cli serv

.PHONY	: all clean fclean
