#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "request.h"
#include "player.h"
#include "sdl.h"
#include "base_map.h"

void	*draw_map_model(void *arg)
{
  int	i, j, a, b, error;
  
  t_data *data = (t_data*)arg;
  error = 0;
  a = 1;
  SDL_Rect wall_src_rect = {71, 175, 16, 16};
  SDL_Rect ground_src_rect = {122, 175, 16, 16};
  SDL_Rect ground_shadowed_rect = {105, 175, 16 ,16};
  for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
      b = 0;
    for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
      SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE,
			    PIXEL_SIZE, PIXEL_SIZE};
      if (j == J_BEGIN || j == J_BEGIN + 12 ||
	  i == I_BEGIN || i == I_BEGIN + 14)
	{
	  error = SDL_RenderCopy(data->renderer, data->texture ,
				 &wall_src_rect, &dest_rect);
	  data->array_map[a][b] = init_t_map(wall_src_rect, dest_rect, wall);
	}
      else if (j == J_BEGIN + 1 ||
	       ( j % 2 != J_BEGIN % 2 && i % 2 == I_BEGIN % 2))
	{
	  error = SDL_RenderCopy(data->renderer, data->texture,
				 &ground_shadowed_rect, &dest_rect);
	  data->array_map[a][b] =
	    init_t_map(ground_shadowed_rect, dest_rect, ground_shadowed);
	}
      else if (i % 2 != I_BEGIN % 2)
	{
	  error = SDL_RenderCopy(data->renderer, data->texture,
				 &ground_src_rect, &dest_rect);
	  	  data->array_map[a][b] =
		    init_t_map(ground_src_rect, dest_rect, ground);
	}
      else if (i % 2 == I_BEGIN % 2)
	{
	  error = SDL_RenderCopy(data->renderer, data->texture,
				 &wall_src_rect, &dest_rect);
	   data->array_map[a][b] =
		    init_t_map(wall_src_rect, dest_rect, wall);
	}
      if (error < 0)
	{
	  SDL_ShowSimpleMessageBox(0, "adding texture in renderer error",
				   SDL_GetError(), data->window);
	  break;
	}
      b++;
    }
    if (error < 0)
      break;
    a++;
  }
  if (error < 0)
    return (NULL);
  return ((void*)data);
}

void	*draw_timer(void *arg)
{
  int	error;

  error = 0;
  t_data *data = (t_data*) arg;
  SDL_Rect timer_panel_rect = {413, 37, 32, 14};
  SDL_Rect dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};
  SDL_Rect dest_rect_timer = {(WINDOW_W / 2) - ((timer_panel_rect.w / 2) * 5),
			      (dest_rect_score.h / 2) -
			      ((timer_panel_rect.h / 2) * 5),
			      timer_panel_rect.w * 5,
			      timer_panel_rect.h * 5};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &timer_panel_rect, &dest_rect_timer);
  data->array_map[0][1] = init_t_map(timer_panel_rect, dest_rect_timer,
				     timer);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Timer Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}


void	*draw_pannel(void *arg)
{
  int	error;

  error = 0;
  t_data *data = (t_data*) arg;
  SDL_Rect score_panel_rect = {414, 175, 256, 32};
  SDL_Rect dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &score_panel_rect, &dest_rect_score);
   data->array_map[0][0] = init_t_map(score_panel_rect, dest_rect_score,
				     pannel);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Score Tab Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}
