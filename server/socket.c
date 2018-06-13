
#include <sys/socket.h>
 #include <netinet/in.h>
#include <netdb.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "server.h"

// init de la socket server.
void 			init_socket(t_server **s) {

  int			socket_fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  sin.sin_addr.s_addr = INADDR_ANY;

  if (bind(socket_fd, (struct sockaddr*)&sin, sizeof (sin)) == -1)
    return;

  if (listen(socket_fd, 42) == -1)
    return;

  (*s)->server_fd = socket_fd;
}
