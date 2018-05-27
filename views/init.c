#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "screen_layout.h"
#include "libmy.h"

//On init la structure avec tous ses champs a NULL
t_screen_info		*init_screen_info() {
  t_screen_info 	*screen_info;
  
  if ((screen_info = malloc(sizeof(*screen_info))) == NULL)
    return NULL;

  screen_info->window 	    	= NULL;
  screen_info->renderer     	= NULL;
  screen_info->menu_background 	= NULL;
  screen_info->join_game 	= NULL;
  screen_info->create_game	= NULL;

  return screen_info;
}

//Init de la window et du renderer
t_screen_info 	*init_window(t_screen_info *screen_info) {
  SDL_Window	*window;
  SDL_Renderer	*renderer;

  window = SDL_CreateWindow(
			    "Bomberman ETNA 2019",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    800,
			    600,
			    SDL_WINDOW_SHOWN
			    );
 
  if (!window) {
    printf("window init error");
    return NULL;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
 
  if (!renderer){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
    return NULL;
  }

  screen_info->window   = window;
  screen_info->renderer = renderer;

  return screen_info;

}



t_screen_info *init_fronts(t_screen_info *screen_info) {
  
  SDL_Surface  *img, *text;
  SDL_Texture  *texture, *texture2;
  SDL_Color    black = {0, 0, 0, 0};
  TTF_Font     *police;
  
  //SDL_IMAGE load an image
  img = IMG_Load("ressources/Bomberman.jpg");
  if (!img){
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), screen_info->window);
  }

  police = TTF_OpenFont("ressources/bm.ttf", 65);
  text = TTF_RenderText_Blended(police, "Bienvenue sur Bomberman", black);
  
  texture = SDL_CreateTextureFromSurface(screen_info->renderer, img);
  texture2 = SDL_CreateTextureFromSurface(screen_info->renderer, text);

  if (!texture){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), screen_info->window);
  }

  screen_info->menu_background = texture;
  screen_info->join_game = texture2;
  return screen_info;
}
