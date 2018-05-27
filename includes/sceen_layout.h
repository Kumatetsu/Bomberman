#ifndef _SCREEN_LAYOUT_
#define _SCREEN_LAYOUT_

typedef struc 	s_screen_info
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture   *menu, *welcome_text;
}		t_screen_info;

s_screen_info	*init_view_context();

#endif
