#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "base_map.h"
#include <stdlib.h>


void *move_player_down(void *arg) {
  t_data *data = (t_data*)arg;
    
  data->players[0].y += 3;
  data->players[0].looking = bomber_d;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].y % 9 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }
        
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_d][data->players[0].index_sprite]), &dest);
    
return (NULL);
}

void *move_player_up(void *arg) {
  t_data *data = (t_data*)arg;
  data->players[0].looking = bomber_u;  
  data->players[0].y -= 3;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].y % 9 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }
        
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_u][data->players[0].index_sprite]), &dest);
    
return (NULL);
}

void *move_player_right(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].looking = bomber_r;
  data->players[0].x += 3;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].x % 9 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }
        
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_r][data->players[0].index_sprite]), &dest);
    
return (NULL);
}

void *move_player_left(void *arg) {
  t_data *data = (t_data*)arg;
   
  data->players[0].x -= 3;
  data->players[0].looking = bomber_l;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].x % 9 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }
        
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_l][data->players[0].index_sprite]), &dest);
    
return (NULL);
}

void *move_player_stop(void *arg) {
  t_data *data = (t_data*)arg;
  
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};
  data->players[0].index_sprite = not_move;
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[data->players[0].looking][not_move]), &dest);  
  return (NULL);
}
