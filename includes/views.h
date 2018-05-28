#ifndef _SCREEN_LAYOUT_
#define _SCREEN_LAYOUT_

typedef struct 	s_screen_info
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture   *menu_background;
  SDL_Texture	*join_game;
  SDL_Texture	*create_game;
}		t_screen_info;

t_screen_info	*init_screen_info();
t_screen_info	*init_window(t_screen_info *screen_info);
t_screen_info   *init_fronts(t_screen_info *screen_info);
#endif
