#ifndef _VIEWS_
#define _VIEWS_

typedef struct 	s_views
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture   *menu_background;
  SDL_Texture	*join_game;
  SDL_Texture	*create_game;
  SDL_Texture   *server_welcome;
  SDL_Texture   *white_back;
}		t_views;

t_views		*init_views();
t_views		*init_window(t_views *views);
t_views   	*init_fronts(t_views *views);
#endif
