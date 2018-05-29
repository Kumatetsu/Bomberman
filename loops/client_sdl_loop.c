#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "views.h"

void		client_loop(t_views *views) {
  int		quit = 0;
  int		x;
  int   	y;
  SDL_Event	event_queue;
  SDL_Rect      join_position = {200, 300, 400, 60};
  SDL_Rect      create_position = {200, 400, 400, 60};
 
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
	  SDL_ShowSimpleMessageBox(0, "Mouse", "you'll join a game!", views->window);
	if (( x > create_position.x ) && ( x < create_position.x + create_position.w ) && ( y > create_position.y ) && ( y < create_position.y + create_position.h ) )
          printf("server button pressed");
	  //SDL_ShowSimpleMessageBox(0, "Mouse", "you'll create a game!", screen_info->window);
	break;
      }
    }
    
    SDL_RenderClear(views->renderer);
    SDL_RenderCopy(views->renderer, views->white_back, NULL, NULL);
    SDL_RenderCopy(views->renderer, views->server_welcome, NULL, &join_position);
    SDL_RenderPresent(views->renderer);
  }
  
  return;
}
