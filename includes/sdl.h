/*
** sdl.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:38:32 2018 hochar_n
** Last update Thu Jul  5 21:38:33 2018 hochar_n
*/

#ifndef _SDL_H_
#define _SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct 	s_sdl
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture   *menu_background;
  SDL_Texture	*join_game;
  SDL_Texture	*create_game;
  SDL_Texture   *server_welcome;
  SDL_Texture   *white_back;
}		t_sdl;

t_sdl		*init_sdl();
t_sdl		*init_window(t_sdl *sdl);
t_sdl   	*init_fronts(t_sdl *sdl);
#endif
