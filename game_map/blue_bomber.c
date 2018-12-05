/*
** blue_bomber.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/game_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:35:13 2018 MASERA Mathieu
** Last update Wed Jul  4 09:35:15 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "player.h"
#include "request.h"
#include "sdl.h"
#include "base_map.h"

void *blue_bomber_sprite(void *arg)
{
  t_data *data = (t_data*)arg;
  data->players[1].bomber_sprites[bomber_d][not_move] = init_rect(70, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_d][move_l] = init_rect(52, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
  data->players[1].bomber_sprites[bomber_d][move_r] = init_rect(88, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
  data->players[1].bomber_sprites[bomber_l][move_l] = init_rect(106, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
  data->players[1].bomber_sprites[bomber_l][move_r] = init_rect(143, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_r][not_move] = init_rect(179, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_r][move_l] = init_rect(160, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_r][transit_move] = init_rect(179, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_r][move_r] = init_rect(197, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_u][not_move] = init_rect(237, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_u][move_l] = init_rect(219, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_u][transit_move] = init_rect(237, 92, 16, 24);
  data->players[1].bomber_sprites[bomber_u][move_r] = init_rect(255, 92, 16, 24);
  data->players[1].bomber_sprites[die][0] = init_rect(345, 92, 16, 24);
  data->players[1].bomber_sprites[die][1] = init_rect(361, 92, 16, 24);
  data->players[1].bomber_sprites[die][2] = init_rect(395, 92, 16, 24);
  return NULL;
}
