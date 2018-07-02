/*
** client.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
** 
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
** 
** Started on  Wed Jun 27 17:03:07 2018 BILLAUD Jean
** Last update Mon Jul  2 18:59:24 2018 BILLAUD Jean
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
#include <SDL2/SDL.h>
#include "sdl.h"
#include "client.h"
#include "player.h"
#include "base_map.h"

//loop SDL du client.
// Pour le moment la socket n'est pas récupérée
void			init_client(t_sdl *sdl)
{
  int			cs;
  char			*addr;
  t_player_request 	*cr;
  addr = enter_addr(sdl);
  cs = client_connect(addr);
  cr = create_player_request();
  start_map(sdl, cs, cr);
  free_player_request(cr);
  
}

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

void		client_loop(t_sdl *sdl, int socket, t_player_request *cr) {
  int			quit = 0;
  //int		x;
  //int   	y;
  SDL_Event		event_queue;
  SDL_Rect		join_position = {200, 300, 400, 60};
  SDL_Color		black = {0, 0, 0, 0};
  TTF_Font		*police;
  fd_set		fd_read;

  police = TTF_OpenFont("ressources/bm.ttf",60);
  sdl->server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, TTF_RenderText_Blended(police, "PATATE", black));
  printf("%d", socket);
  cr->command = 1;

    while(!quit) {
    //FD_SET(STDIN_FILENO, &fd_read);
    //printf("toto");
    if (select((socket + 1), &fd_read, NULL, NULL, NULL) == -1)
      {
	quit = 1;
      }

    while(SDL_PollEvent(&event_queue)) {
      switch(event_queue.type){
      case SDL_QUIT:
	quit = 1;
	break;
      case SDL_KEYUP:
	break;
      case SDL_KEYDOWN:
	switch(event_queue.key.keysym.sym){
	case SDLK_UP:
	  printf("up\n");
	  send_request(socket, cr);
	  fseek(stdin,0,SEEK_END);
	  break;
	case SDLK_DOWN:
	  printf("down\n");
	  send_request(socket, cr);
	  fseek(stdin,0,SEEK_END);
	  break;
	case SDLK_RIGHT:
	  printf("right\n");
	  send_request(socket, cr);
	  fseek(stdin,0,SEEK_END);
	  break;
	case SDLK_LEFT:
	  printf("left\n");
	  send_request(socket, cr);
	  fseek(stdin,0,SEEK_END);
	  break;
	}
      }
    }
    
    if (FD_ISSET(socket, &fd_read))
      {
	printf("tata\n");
	if (get_message(socket) == 0){
	  quit = 1;
	}
      }

    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->white_back, NULL, NULL);
    SDL_RenderCopy(sdl->renderer, sdl->server_welcome, NULL, &join_position);
    SDL_RenderPresent(sdl->renderer);
    SDL_SetRenderTarget(sdl->renderer, NULL);
  }

  return;
}
