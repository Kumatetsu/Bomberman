#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "base_map.h"

void	*draw_player_1(void *arg) {
  int	error;

  error = 0;
  t_data *data = (t_data*)arg;
  SDL_Rect dest_rect = {(I_BEGIN + 1) * 48, ((J_BEGIN + 1) * 48) - 36 ,
			16 * 3, 24 * 3};
  data->players[0].x = (I_BEGIN + 1) * 48;
  data->players[0].y = ((J_BEGIN + 1) * 48) - 24;
  data->players[0].index_sprite = not_move;
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &(data->players[0].bomber_sprites[bomber_d][not_move]),
			 &dest_rect);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player1 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}

//blue bomber
void	*draw_player_2(void *arg) {
  int	error;

  error = 0;
  t_data *data = (t_data*)arg;
  SDL_Rect dest_rect = {(I_BEGIN + 13) * 48, ((J_BEGIN + 11) * 48) - 36 ,
			16 * 3, 24 * 3};
  data->players[1].x = (I_BEGIN + 13) * 48;
  data->players[1].y = ((J_BEGIN + 11) * 48) - 36;
  data->players[1].index_sprite = not_move;
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &(data->players[1].bomber_sprites[bomber_u][not_move]),
			 &dest_rect);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player2 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}

//black bomber
void	*draw_player_3(void *arg) {
  int	error;

  error = 0;
  t_data *data = (t_data*)arg;
  SDL_Rect dest_rect = {(I_BEGIN + 1) * 48, ((J_BEGIN + 11) * 48) - 36 ,
			16 * 3, 24 * 3};
  data->players[2].x = (I_BEGIN + 1) * 48;
  data->players[2].y = ((J_BEGIN + 11) * 48) - 36;
  data->players[2].index_sprite = not_move;
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &(data->players[2].bomber_sprites[bomber_u][not_move]),
			 &dest_rect);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player3 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}

//red bomber
void	*draw_player_4(void *arg) {
  int	error;

  error = 0;
  t_data *data = (t_data*)arg;
  SDL_Rect dest_rect = {(I_BEGIN + 13) * 48, ((J_BEGIN + 1) * 48) - 36 ,
			16 * 3, 24 * 3};
  data->players[3].x = (I_BEGIN + 13) * 48;
  data->players[3].y = ((J_BEGIN + 1) * 48) - 36;
  data->players[3].index_sprite = not_move;
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &(data->players[3].bomber_sprites[bomber_d][not_move]),
			 &dest_rect);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player4 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}


