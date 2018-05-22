#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>

int main ()
{
  int 	     quit = 0;
  SDL_Window *window;
  SDL_Event  event;

  //init sdl
  SDL_Init(SDL_INIT_VIDEO);

  //init the window
  window = SDL_CreateWindow(
			    "Bomberman",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    800,
			    600,
			    SDL_WINDOW_SHOWN
			    );
  if (window == NULL) {
    printf("windows not created");
    return 1;
  }

  while(!quit) {
    SDL_WaitEvent(&event);

    switch(event.type){
    case SDL_QUIT:
      quit = 1;
      break;
    }
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
