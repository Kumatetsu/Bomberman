#ifndef _SCREEN_LAYOUT_
#define _SCREEN_LAYOUT_

typedef struct 	s_screen_info
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture   *menu, *welcome_text;
}		t_screen_info;

t_screen_info	*init_view_context();
t_screen_info   *create_menu(t_screen_info *screen_info);
#endif
