
CC 	= gcc

CFLAGS 	= -W -Werror -Wextra -Wall -pedantic -g -Iinclude/

CLI_SRC =	client/client.c				    \
			client/create_cli_socket.c	    \
			client/client_loop.c		    \
			client/client_request.c         \
			common/request_communication.c  \

SRV_SRC =	server/server.c 			    \
			server/create_srv_socket.c 	    \
			server/create_srv_struct.c 	    \
			server/srv_actions.c 		    \
			server/moving.c      		    \
			server/create_server.c 		    \
			server/main_loop.c			    \
			common/request_communication.c  \

CLI_OBJ = ${CLI_SRC:%.c=%.o}

SRV_OBJ = ${SRV_SRC:%.c=%.o}

RM 	= rm -rf

all: cli serv

re 	: clean all

cli	:	$(CLI_OBJ)
		$(CC) $(CFLAGS)		$(CLI_OBJ) 	-o	cli

serv :	$(SRV_OBJ)
		$(CC) $(CFLAGS)		$(SRV_OBJ) 	-o	serv

clean :
	  $(RM) $(CLI_OBJ) $(SRV_OBJ)

fclean 	: clean
	  $(RM) cli serv

.PHONY	: all clean fclean
