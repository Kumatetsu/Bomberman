#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "views.h"
#include "libmy.h"

//On init la structure avec tous ses champs a NULL
t_screen_info 		*init_screen_info()
{
  t_screen_info 	*screen_info;

  if ((screen_info = malloc(sizeof(*screen_info))) == NULL)
    return NULL;
  
  screen_info->window = NULL;
  screen_info->renderer = NULL;
  screen_info->menu_background = NULL;
  screen_info->join_game = NULL;
  screen_info->create_game = NULL;
  
  return screen_info;
}

//Init de la window et du renderer
t_screen_info *init_window(t_screen_info *screen_info)
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  
  window = SDL_CreateWindow(
			    "Bomberman ETNA 2019",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    800,
			    600,
			    SDL_WINDOW_SHOWN);
  
  if (!window)
    {
      printf("window init error");
      return NULL;
    }
  
  renderer = SDL_CreateRenderer(window, -1, 0);
  
  if (!renderer)
    {
      SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
      return NULL;
    }
  
  screen_info->window = window;
  screen_info->renderer = renderer;
  
  return screen_info;
}

t_screen_info *init_fronts(t_screen_info *screen_info)
{
  
  SDL_Surface *img, *join_game_text, *create_server_text;
  SDL_Texture *background_texture, *join_texture, *server_texture;
  SDL_Color black = {0, 0, 0, 0};
  TTF_Font *police;
  
  //SDL_IMAGE load an image
  img = IMG_Load("ressources/Bomberman.jpg");
  if (!img)
    {
      SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), screen_info->window);
    }
  
  police = TTF_OpenFont("ressources/bm.ttf", 65);
  join_game_text = TTF_RenderText_Blended(police, "join_game", black);
  create_server_text = TTF_RenderText_Blended(police, "create_server", black);
  
  background_texture = SDL_CreateTextureFromSurface(screen_info->renderer, img);
  join_texture = SDL_CreateTextureFromSurface(screen_info->renderer, join_game_text);
  server_texture = SDL_CreateTextureFromSurface(screen_info->renderer, create_server_text);
  
  if (!background_texture || !join_texture || !server_texture )
    {
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), screen_info->window);
    }
  
  screen_info->menu_background = background_texture;
  screen_info->join_game = join_texture;
  screen_info->create_game = server_texture;

  return screen_info;
}
