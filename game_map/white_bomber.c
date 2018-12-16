/*
** white_bomber.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/game_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:36:14 2018 MASERA Mathieu
** Last update Wed Jul  4 09:36:15 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include "enum.h"
#include "sdl.h"
#include "map.h"
#include "player_info.h"
#include "data.h"
#include "base_map_manager.h"
#include "game_map.h"

void *white_bomber_sprite(void *arg)
{
  t_data *data = (t_data*)arg;
  data->players[0].bomber_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_d][move_l] = init_rect(52, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_d][move_r] = init_rect(88, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_l][move_l] = init_rect(106, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_l][move_r] = init_rect(143, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_r][not_move] = init_rect(179, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_r][move_l] = init_rect(160, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_r][transit_move] = init_rect(179, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_r][move_r] = init_rect(197, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_u][not_move] = init_rect(237, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_u][move_l] = init_rect(219, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_u][transit_move] = init_rect(237, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_u][move_r] = init_rect(255, 38, 16, 24);
  data->players[0].bomber_sprites[die][0] = init_rect(345, 38, 16, 24);
  data->players[0].bomber_sprites[die][1] = init_rect(361, 38, 16, 24);
  data->players[0].bomber_sprites[die][2] = init_rect(395, 38, 16, 24);
  return NULL;
}
