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
  SDL_Rect      position = {100, 200, 400, 60};
  SDL_Surface  *img, *text;
  SDL_Texture  *texture, *texture2;
  SDL_Color    black = {0, 0, 0, 0};
  TTF_Font     *police;
  
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();

  
  
  
  
  

  police = TTF_OpenFont("ressources/ASMAN.TTF", 65);
  text = TTF_RenderText_Blended(police, "Bienvenue sur Bomberman", black);
  
  texture = SDL_CreateTextureFromSurface(renderer, img);
  texture2 = SDL_CreateTextureFromSurface(renderer, text);

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
    SDL_RenderCopy(renderer, texture2, NULL, &position);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  TTF_CloseFont(police);
  SDL_FreeSurface(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
