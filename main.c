#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <screen_layout.h>

int main ()
{
  int 	        quit = 0;

  SDL_Event     event;

  SDL_Rect      position = {100, 200, 400, 60};
  t_screen_info *screen_info;
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();
  
  screen_info = init_screen_info();
  screen_info = init_window(screen_info);
  screen_info = init_fronts(screen_info);
  

  
  while(!quit) {
    SDL_WaitEvent(&event);

    switch(event.type){
    case SDL_QUIT:
      quit = 1;
      break;
    }
    
    SDL_RenderCopy(screen_info->renderer, screen_info->menu_background, NULL, NULL);
    SDL_RenderCopy(screen_info->renderer, screen_info->join_game, NULL, &position);
    SDL_RenderPresent(screen_info->renderer);
  }

  SDL_DestroyTexture(screen_info->menu_background);
  SDL_DestroyRenderer(screen_info->renderer);
  SDL_DestroyWindow(screen_info->window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
