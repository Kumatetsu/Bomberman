#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "views.h"
#include "loops.h"

int main ()
{
  t_views *views;
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();
  
  views = init_views();
  views = init_window(views);
  views = init_fronts(views);
  

  sdl_loop(views);

  SDL_DestroyTexture(views->menu_background);
  SDL_DestroyRenderer(views->renderer);
  SDL_DestroyWindow(views->window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
