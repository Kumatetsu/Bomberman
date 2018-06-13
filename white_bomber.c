#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "base_map.h"

void *white_bomber_sprite(void *arg)
{
  t_data *data = (t_data*)arg;
  data->players[0].bomber_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_d][bomber_l] = init_rect(52, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_d][bomber_r] = init_rect(88, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_l][bomber_l] = init_rect(106, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_l][bomber_r] = init_rect(143, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_r][not_move] = init_rect(179, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_r][bomber_l] = init_rect(160, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_r][bomber_r] = init_rect(197, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_u][not_move] = init_rect(237, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_u][bomber_l] = init_rect(219, 38, 16, 24);
   data->players[0].bomber_sprites[bomber_u][bomber_r] = init_rect(255, 38, 16, 24);
   data->players[0].bomber_sprites[die][0] = init_rect(345, 38, 16, 24);
   data->players[0].bomber_sprites[die][1] = init_rect(361, 38, 16, 24);
   data->players[0].bomber_sprites[die][2] = init_rect(395, 38, 16, 24);
  return NULL;
}
