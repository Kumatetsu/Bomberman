#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <screen_layout.h>

t_screen_info	*init_view_context() {
  t_screen_info *screen_info;
  
  if ((screen_info = malloc(sizeof(*screen_info))) == NULL)
    return NULL;

  screen_info->window 	    = NULL;
  screen_info->renderer     = NULL;
  screen_info->menu 	    = NULL;
  screen_info->welcome_text = NULL;
  
  return screen_info;
}

t_screen_info *create_menu(t_screen_info *screen_info) {
  
  SDL_Window   *window;
  SDL_Renderer *renderer;
  SDL_Surface  *img, *text;
  SDL_Texture  *texture, *texture2;
  SDL_Color    black = {0, 0, 0, 0};
  TTF_Font     *police;

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
    return NULL;
  }

  //where the image will be rendered
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }
  
  //SDL_IMAGE load an image
  img = IMG_Load("ressources/Bomberman.jpg");
  if (!img){
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), window);
  }

  police = TTF_OpenFont("ressources/ASMAN.TTF", 65);
  text = TTF_RenderText_Blended(police, "Bienvenue sur Bomberman", black);
  
  texture = SDL_CreateTextureFromSurface(renderer, img);
  texture2 = SDL_CreateTextureFromSurface(renderer, text);

  if (!texture){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }


  screen_info->window = window;
  screen_info->renderer = renderer;
  screen_info->menu = texture;
  screen_info->welcome_text = texture2;
  return screen_info;
}
