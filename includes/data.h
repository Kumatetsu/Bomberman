#ifndef _DATA_H_
#define _DATA_H_

// need sdl, player_info.h, base_map_manager.h
typedef struct	s_data
{
  SDL_Texture	*texture;
  SDL_Renderer	*renderer;
  SDL_Window	*window;
  t_map		array_map[14][15];
  t_player_info	players[4];
  SDL_Rect	destroyable[3][3];
}		t_data;

#endif /* !_DATA_H_ */
