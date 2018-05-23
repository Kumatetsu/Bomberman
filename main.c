#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main ()
{
  int 	        quit = 0;
  SDL_Window   *window;
  SDL_Event     event;
  SDL_Renderer *renderer;
  SDL_Surface  *img;
  SDL_Texture  *texture;
  
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  
  //init the window
  window = SDL_CreateWindow(
			    "Bomberman",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    800,
			    600,
			    SDL_WINDOW_SHOWN
			    );  
  if (!window) {
    printf("windows not created");
    return 1;
  }
  
  //where the image will be rendered
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }
  
  //SDL_IMAGE load an image
  img = IMG_Load("Bomberman.jpg");
  if (!img){
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), window);
  }

  texture = SDL_CreateTextureFromSurface(renderer, img);
  if (!texture){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }
  
  while(!quit) {
    SDL_WaitEvent(&event);

    switch(event.type){
    case SDL_QUIT:
      quit = 1;
      break;
    }
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
