/*
** client.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**** Started on  Wed Jun 27 17:03:07 2018 BILLAUD Jean
** Last update Tue Jul  3 23:30:31 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netdb.h>
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

// loop SDL du client.
// Pour le moment la socket n'est pas récupérée
void			init_client(t_sdl *sdl)
{
  int			cs;
  char			*addr;

  // on attend que l'adresse soit écrite par le user (ce fichier, client/client.c)
  addr = enter_addr(sdl);
  // une fois l'adresse ip écrite, on tente de connecter (client/socket.c)
  cs = client_connect(addr);
  // on démarre la boucle cliente (start_map.c)
  start_map(sdl, cs);

}

// Fonction gérant l'écriture de l'ip dans le menu après un click sur 'join server'
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

  police = TTF_OpenFont("ressources/bm.ttf",60);
  addr = malloc(sizeof(*addr));
  memset(addr, 0, sizeof(*addr));
  sdl->server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, addr, black));
  sdl->join_game = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, "Connect", black));
  SDL_StartTextInput();
  while(!quit) {
    while(SDL_PollEvent(&event_queue)) {
      switch(event_queue.type){
      case SDL_QUIT:
	  quit = 1;
	  addr = NULL;
	  break;
      case SDL_KEYDOWN:
	switch(event_queue.key.keysym.sym ){
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

      if (( x > connect.x ) && ( x < connect.x + connect.w ) && ( y > connect.y ) && ( y < connect.y + connect.h ) )
	if (strlen(addr) >= 7 && strlen(addr) <= 15)
	  quit = 1;
      }
    }
    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->white_back, NULL, NULL);
    SDL_RenderCopy(sdl->renderer, sdl->server_welcome, NULL, &join_position);
    SDL_RenderCopy(sdl->renderer, sdl->join_game, NULL, &connect);
    SDL_RenderPresent(sdl->renderer);
    SDL_SetRenderTarget(sdl->renderer, NULL);
  }
  return addr;
}

//init de la socket client + connection à une socket server.
int			client_connect(char *serv_addr)
{
  struct protoent       *pe;
  struct sockaddr_in    sin;
  int			s;
  int			port;

  memset(&sin, 0, sizeof(struct sockaddr_in));
  port = PORT;
  pe = getprotobyname("TCP");
  if (pe == NULL)
    {
      printf("error protocole for socket client");
      return (-1);
    }
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    {
      printf("error socket client");
      return (-1);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(serv_addr);
  if(connect(s, (const struct sockaddr *)&sin, sizeof (sin)) == -1)
    {
      printf("error connection\n");
      exit(errno);
    }
  printf("connected\n");
  return (s);
}
