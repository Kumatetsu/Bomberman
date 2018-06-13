#ifndef _SDL_H_
#define _SDL_H_

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
