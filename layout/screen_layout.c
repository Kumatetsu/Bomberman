#include <SDL2/SDL.h>
#include <../includes/screen_layout.h>

s_screen_info	*init_view_context() {
  s_screen_info *screen_info;
  
  if ((screen_info = malloc(sizeof(*screen_info))) == NULL)
    return NULL;

  screen_info->window 	    = NULL;
  screen_info->renderer     = NULL;
  screen_info->menu 	    = NULL;
  screen_info->welcome_text = NULL;
  
  return screen_info;
}

s_screen_info *create_menu(s_screen_info *screen_info) {
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
  img = IMG_Load("ressources/Bomberman.jpg");
  if (!img){
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), window);
  }

  screen_info->window = window;
  screen_info->renderer = renderer;
  screen_info->menu = img;
  return screen_info;
}
