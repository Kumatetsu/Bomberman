/*
** client.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**** Started on  Wed Jun 27 17:03:07 2018 BILLAUD Jean
** Last update Tue Jul  3 23:30:31 2018 MASERA Mathieu
*/

#include "system.h"
#include <errno.h>
#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "map.h"
#include "server.h"
#include "client.h"
#include "start_map.h"
#include "base_map_manager.h"

// SDL loop of the client.
// The socket is not set yet
void	init_client(t_sdl *sdl)
{
  int	cs;
  char	*addr;

  // we wait the adresse get written by the user(this file, client/client.c)
  addr = enter_addr(sdl);
  // when the ip adress is written, we try to connect (client/socket.c)
  cs = client_connect(addr);
  // we start the client loop
  start_map(sdl, cs);
}

// This function manage the write of the ip after the click on 'join server' in the menu
char		*enter_addr(t_sdl *sdl)
{
  int		quit = 0;
  SDL_Event	event_queue;
  char		*addr;
  void 		*foo;
  SDL_Rect      join_position = {200, 300, 400, 60};
  SDL_Rect      connect = {200, 400, 400, 60};
  SDL_Color 	black = {0, 0, 0, 0};
  TTF_Font 	*police;
  int		x;
  int		y;

  #ifdef linux
    police = TTF_OpenFont("/usr/share/bomberman/ressources/bm.ttf",60);
  #else
    police = TTF_OpenFont("ressources/bm.ttf",60);
  #endif
  addr = malloc(sizeof(*addr));
  memset(addr, 0, sizeof(*addr));
  sdl->server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, addr, black));
  sdl->join_game = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, "Connect", black));
  SDL_StartTextInput();
  while (!quit)
    {
      while (SDL_PollEvent(&event_queue))
	{
	  switch(event_queue.type)
	    {
	    case SDL_QUIT:
	      quit = 1;
	      addr = NULL;
	      break;
	    case SDL_KEYDOWN:
	      switch (event_queue.key.keysym.sym)
		{
		case SDLK_BACKSPACE:
		  if (addr != NULL) {
		    free(addr);
		  }
		  addr = malloc(sizeof(*addr));
		  memset(addr, 0, sizeof(*addr));
		  sdl->server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, addr, black));
		  break;
		}
	      break;
	    case SDL_TEXTINPUT:
	      foo = (char *)realloc(addr, (strlen(addr) + 2));
	      addr = foo;
	      strcat(addr, event_queue.text.text);
	      sdl->server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, addr, black));
	      break;
	    case SDL_MOUSEBUTTONDOWN:
	      x = event_queue.button.x;
	      y = event_queue.button.y;

	      if ((x > connect.x) && (x < connect.x + connect.w) && (y > connect.y) && (y < connect.y + connect.h)) {
		if (strlen(addr) >= 7 && strlen(addr) <= 15) {
		  quit = 1;
		}
	      }
	    }
	}
      SDL_RenderClear(sdl->renderer);
      SDL_RenderCopy(sdl->renderer, sdl->white_back, NULL, NULL);
      SDL_RenderCopy(sdl->renderer, sdl->server_welcome, NULL, &join_position);
      SDL_RenderCopy(sdl->renderer, sdl->join_game, NULL, &connect);
      SDL_RenderPresent(sdl->renderer);
      SDL_SetRenderTarget(sdl->renderer, NULL);
    }
  return (addr);
}

//initialisation of the client socket and connection to a server socket
int			client_connect(char *serv_addr)
{
  struct protoent       *pe;
  SOCKADDR_IN		sin;
  SOCKET		s;
  int			port;

  memset(&sin, 0, sizeof(SOCKADDR_IN));
  port = PORT;
  pe = getprotobyname("TCP");
  if (pe == NULL) {
    printf("error protocole for socket client");
    return (-1);
  }
  
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);

#ifdef _WIN32
  if (s == INVALID_SOCKET) {
    printf("error socket client");
    return (-1);
  }
#else
  if (s == -1) {
    printf("error socket client");
    return (-1);
  }
#endif
	
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(serv_addr);
  if(connect(s, (const SOCKADDR *)&sin, sizeof (sin)) != 0) {
#ifdef _WIN32
    printf("error connection connect client.c : %d\n", WSAGetLastError());
#else
    printf("error connection\n");
#endif
    exit(errno);
  }
  printf("connected\n");
  return (s);
}
