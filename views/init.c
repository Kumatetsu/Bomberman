#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "views.h"
#include "libmy.h"

//On init la structure avec tous ses champs a NULL
t_views 		*init_views()
{
  t_views 		*views;

  if ((views = malloc(sizeof(*views))) == NULL)
    return NULL;
  
  views->window = NULL;
  views->renderer = NULL;
  views->menu_background = NULL;
  views->join_game = NULL;
  views->create_game = NULL;
  views->server_welcome = NULL;
  views->white_back = NULL;

  return views;
}

//Init de la window et du renderer
t_views *init_window(t_views *views)
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
  
  views->window = window;
  views->renderer = renderer;
  
  return views;
}

t_views *init_fronts(t_views *views)
{
  
  SDL_Surface *img, *join_game_text, *create_server_text, *server_welcome_text, *white;
  SDL_Texture *background_texture, *join_texture, *server_texture, *server_welcome, *white_back;
  SDL_Color black = {0, 0, 0, 0};
  TTF_Font *police;
  
  //SDL_IMAGE load an image
  img = IMG_Load("ressources/Bomberman.jpg");
  white = IMG_Load("ressources/white.jpg");
  if (!img || !white)
    {
      SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), views->window);
    }
  
  police = TTF_OpenFont("ressources/bm.ttf", 65);
  join_game_text = TTF_RenderText_Blended(police, "join_game", black);
  create_server_text = TTF_RenderText_Blended(police, "create_server", black);
  server_welcome_text = TTF_RenderText_Blended(police, "WELCOME SERVER", black);

  background_texture = SDL_CreateTextureFromSurface(views->renderer, img);
  white_back = SDL_CreateTextureFromSurface(views->renderer, white);

  join_texture = SDL_CreateTextureFromSurface(views->renderer, join_game_text);
  server_texture = SDL_CreateTextureFromSurface(views->renderer, create_server_text);
  server_welcome = SDL_CreateTextureFromSurface(views->renderer, server_welcome_text);

  if (!background_texture || !join_texture || !server_texture )
    {
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), views->window);
    }
  
  views->menu_background = background_texture;
  views->white_back = white_back;
  views->join_game = join_texture;
  views->create_game = server_texture;
  views->server_welcome = server_welcome;

  return views;
}
