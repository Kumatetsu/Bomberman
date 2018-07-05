/*
** init.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/sdl
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:37:04 2018 MASERA Mathieu
** Last update Wed Jul  4 09:37:07 2018 MASERA Mathieu
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sdl.h"
#include "libmy.h"
#include "request.h"
#include "player.h"
#include "base_map.h"

//On init la structure avec tous ses champs a NULL
t_sdl 		*init_sdl()
{
  t_sdl 		*sdl;

  if ((sdl = malloc(sizeof(t_sdl))) == NULL)
    return NULL;

  sdl->window = NULL;
  sdl->renderer = NULL;
  sdl->menu_background = NULL;
  sdl->join_game = NULL;
  sdl->create_game = NULL;
  sdl->server_welcome = NULL;
  sdl->white_back = NULL;

  return sdl;
}

//Init de la window et du renderer
t_sdl *init_window(t_sdl *sdl)
{
  SDL_Window *window;
  SDL_Renderer *renderer;

  window = SDL_CreateWindow(
			    "Bomberman ETNA 2019",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    WINDOW_W,
			    WINDOW_H,
			    SDL_WINDOW_SHOWN);

  if (!window)
    return NULL;

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer)
    {
      SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
      return NULL;
    }

  sdl->window = window;
  sdl->renderer = renderer;

  return sdl;
}

t_sdl *init_fronts(t_sdl *sdl)
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
      SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), sdl->window);
    }

  police = TTF_OpenFont("ressources/bm.ttf", 65);
  join_game_text = TTF_RenderText_Blended(police, "join_game", black);
  create_server_text = TTF_RenderText_Blended(police, "create_server", black);
  server_welcome_text = TTF_RenderText_Blended(police, "WELCOME SERVER", black);

  background_texture = SDL_CreateTextureFromSurface(sdl->renderer, img);
  white_back = SDL_CreateTextureFromSurface(sdl->renderer, white);

  join_texture = SDL_CreateTextureFromSurface(sdl->renderer, join_game_text);
  server_texture = SDL_CreateTextureFromSurface(sdl->renderer, create_server_text);
  server_welcome = SDL_CreateTextureFromSurface(sdl->renderer, server_welcome_text);

  if (!background_texture || !join_texture || !server_texture )
    {
      SDL_ShowSimpleMessageBox(0, "init texture error", SDL_GetError(), sdl->window);
    }
  //we clean surface as we converted them to texture so we don't need them anymore
  SDL_FreeSurface(img);
  SDL_FreeSurface(white);
  SDL_FreeSurface(join_game_text);
  SDL_FreeSurface(create_server_text);
  SDL_FreeSurface(server_welcome_text);
  TTF_CloseFont(police);
  sdl->menu_background = background_texture;
  sdl->white_back = white_back;
  sdl->join_game = join_texture;
  sdl->create_game = server_texture;
  sdl->server_welcome = server_welcome;

  return sdl;
}
