/*
** main.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Mon Jul  2 18:46:25 2018 BILLAUD Jean
*/

#include "system.h"
#include "sdl.h"
#include "menu.h"
#include "request.h"
#include "player.h"
#include "player_info.h"
#include "base_map.h"

int main (int argc, char *argv[])
{
  t_sdl *sdl;

  printf("\n Nombre d'arguments: %d", argc);
  int iterator = 0;
  while (iterator < argc) {
    printf("\n - n°%d: %s", iterator, argv[iterator]);
    ++iterator;
  }
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();

  sdl = init_sdl();
  sdl = init_window(sdl);
  sdl = init_fronts(sdl);

  //comment maiemacs n to see start_map working ;)
  main_menu(sdl);
  SDL_DestroyTexture(sdl->menu_background);
  SDL_DestroyTexture(sdl->white_back);
  SDL_DestroyTexture(sdl->join_game);
  SDL_DestroyTexture(sdl->create_game);
  SDL_DestroyTexture(sdl->server_welcome);
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  free(sdl);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
