#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "sdl.h"
#include "client.h"

//loop SDL du client.
// Pour le moment la socket n'est pas récupérée
void		client_loop(t_sdl *sdl) {
  int		quit = 0;
  int		x;
  int   	y;
  SDL_Event	event_queue;
  SDL_Rect      join_position = {200, 300, 400, 60};

  my_connect();

  while(!quit) {
    while(SDL_PollEvent(&event_queue)) {
      switch(event_queue.type){
      case SDL_QUIT:
	quit = 1;
	break;
      case SDL_MOUSEBUTTONDOWN:
	x = event_queue.button.x;
	y = event_queue.button.y;

	if (( x > join_position.x ) && ( x < join_position.x + join_position.w ) && ( y > join_position.y ) && ( y < join_position.y + join_position.h ) )
	  SDL_ShowSimpleMessageBox(0, "Mouse", "you'll join a game!", sdl->window);
	break;
      }
      //CASE KEYPRESS:
      // keyaction();
    }

    //render updates from server
    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->white_back, NULL, NULL);
    SDL_RenderCopy(sdl->renderer, sdl->server_welcome, NULL, &join_position);
    SDL_RenderPresent(sdl->renderer);
  }

  return;
}
