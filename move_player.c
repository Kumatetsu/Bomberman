/*
** game_event.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:29:38 2018 MASERA Mathieu
** Last update Wed Jul  4 09:29:40 2018 MASERA Mathieu
*/

#include <stdlib.h>
// sur
#include "enum.h"
#include "sdl.h"
#include "map.h"
#include "player_info.h"
#include "data.h"
#include "move_player.h"
#include "constant.h"

void *move_player_down(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].y += 6;
  data->players[0].current_dir = bomber_d;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, PIXEL_SIZE, 24 * 3};

  if (data->players[0].y % 18 == 0) {
    if (data->players[0].direction_sprite == 3) {
      data->players[0].direction_sprite = not_move;
    } else {
      data->players[0].direction_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_d][data->players[0].direction_sprite]), &dest);

return (NULL);
}

void *move_player_up(void *arg) {
  t_data *data = (t_data*)arg;
  data->players[0].current_dir = bomber_u;
  data->players[0].y -= 6;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, PIXEL_SIZE, 24 * 3};

  if (data->players[0].y % 18 == 0) {
    if (data->players[0].direction_sprite == 3) {
      data->players[0].direction_sprite = not_move;
    } else {
      data->players[0].direction_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_u][data->players[0].direction_sprite]), &dest);

return (NULL);
}

void *move_player_right(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].current_dir = bomber_r;
  data->players[0].x += 6;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, PIXEL_SIZE, 24 * 3};

  if (data->players[0].x % 18 == 0) {
    if (data->players[0].direction_sprite == 3) {
      data->players[0].direction_sprite = not_move;
    } else {
      data->players[0].direction_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_r][data->players[0].direction_sprite]), &dest);

return (NULL);
}

void *move_player_left(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].x -= 6;
  data->players[0].current_dir = bomber_l;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, PIXEL_SIZE, 24 * 3};

  if (data->players[0].x % 18 == 0) {
    if (data->players[0].direction_sprite == 3) {
      data->players[0].direction_sprite = not_move;
    } else {
      data->players[0].direction_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_l][data->players[0].direction_sprite]), &dest);

return (NULL);
}

void *move_player_stop(void *arg) {
  t_data *data = (t_data*)arg;

  SDL_Rect dest = {data->players[0].x, data->players[0].y, PIXEL_SIZE, 24 * 3};
  data->players[0].direction_sprite = not_move;
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[data->players[0].current_dir][not_move]), &dest);
  return (NULL);
}
