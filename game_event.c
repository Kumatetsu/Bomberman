#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "base_map.h"
#include <stdlib.h>
//#include <stdio.h>

void *move_player(void *arg) {
  t_data *data = (t_data*)arg;
    
    data->players[0].y += 1;
    SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};
    if (data->players[0].y % 3 ) {
        SDL_RenderCopy(data->renderer, data->texture,
			       &(data->players[0].bomber_sprites[bomber_d][bomber_r]), &dest);
    }
    else if (data->players[0].y %2) {
        SDL_RenderCopy(data->renderer, data->texture,
			       &(data->players[0].bomber_sprites[bomber_d][bomber_l]), &dest);
    } else {
        SDL_RenderCopy(data->renderer, data->texture,
			       &(data->players[0].bomber_sprites[bomber_d][bomber_d]), &dest);
    }
    
 return (NULL);
}
