#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main ()
{
  int 	        quit = 0;
  SDL_Window   *window;
  SDL_Event     event;
  SDL_Renderer *renderer;
  SDL_Surface  *img, *text;
  SDL_Texture  *texture, *texture2;
  SDL_Color    black = {0, 0, 0, 0};
  TTF_Font     *police;
  
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();
  
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

  police = TTF_OpenFont("ASMAN.TTF", 65);
  text = TTF_RenderText_Blended(police, "Bienvenue sur Bomberman", black);
  
  texture = SDL_CreateTextureFromSurface(renderer, img);
  if (!texture){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }

  texture2 = SDL_CreateTextureFromSurface(renderer, text);
  
  while(!quit) {
    SDL_WaitEvent(&event);

    switch(event.type){
    case SDL_QUIT:
      quit = 1;
      break;
    }
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderCopy(renderer, texture2, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(img);
  TTF_CloseFont(police);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
