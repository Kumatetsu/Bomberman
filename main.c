#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "menu.h"

int main ()
{
  t_sdl *sdl;
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();

  sdl = init_sdl();
  sdl = init_window(sdl);
  sdl = init_fronts(sdl);


  main_menu(sdl);

  SDL_DestroyTexture(sdl->menu_background);
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
