/*
** start_map.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:30:11 2018 MASERA Mathieu
** Last update Wed Jul  4 09:30:12 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "sdl.h"
#include "client.h"
#include "player_info.h"
#include "player.h"
#include "base_map.h"
#include "game_info.h"
#include "thread.h"
#include "game_info_serialization.h"


int start_map(t_sdl *sdl, int socket, t_player_request *cr)
{
  int quit;
  SDL_Event event;
  t_data *data;
  pthread_t listen_server;

  quit = 0;
  data = malloc(sizeof(*data));
  data->renderer = sdl->renderer;
  data->window = sdl->window;
  init_sprites_sheet((void *)data);
  draw_all((void *)data);
  SDL_SetRenderTarget(data->renderer, NULL);
  SDL_RenderPresent(data->renderer);
  SDL_RenderClear(data->renderer);
  printf("\nbefore create thread\n");
  if (pthread_create(&listen_server, NULL, thread_listen_serv, &socket))
  {
    quit = 1;
  }
  printf("\nthread created\n");
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYUP:
      {
        SDL_RenderClear(data->renderer);
        rebuild_map((void *)data);
        move_player_stop((void *)data);
        SDL_RenderPresent(data->renderer);
        SDL_SetRenderTarget(data->renderer, NULL);
        break;
      }
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
          SDL_RenderClear(data->renderer);
          rebuild_map((void *)data);
          move_player_up((void *)data);
          send_request(socket, cr);
          break;
        case SDLK_LEFT:
          SDL_RenderClear(data->renderer);
          rebuild_map((void *)data);
          move_player_left((void *)data);
          send_request(socket, cr);
          break;
        case SDLK_RIGHT:
          SDL_RenderClear(data->renderer);
          rebuild_map((void *)data);
          move_player_right((void *)data);
          send_request(socket, cr);
          break;
        case SDLK_DOWN:
          SDL_RenderClear(data->renderer);
          rebuild_map((void *)data);
          move_player_down((void *)data);
          send_request(socket, cr);
          break;
        }
        SDL_RenderPresent(data->renderer);
        SDL_SetRenderTarget(data->renderer, NULL);
      }
    }
  }
  pthread_cancel(listen_server);
  SDL_DestroyTexture(data->texture);
  free(data);
  return 0;
}

void *init_sprites_sheet(void *arg)
{
  SDL_Texture *sprite_texture;
  SDL_Surface *sprites_img;

  t_data *data = (t_data *)arg;
  sprites_img = NULL;
  sprite_texture = NULL;
  IMG_Init(IMG_INIT_PNG);

  sprites_img = IMG_Load("./ressources/bombermanSprite.PNG");
  if (!sprites_img)
  {
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(),
                             data->window);
  }

  //we create the image as a texture to insert it in renderer
  sprite_texture = SDL_CreateTextureFromSurface(data->renderer,
                                                sprites_img);

  if (!sprite_texture)
  {
    SDL_ShowSimpleMessageBox(0, "texture image init error",
                             SDL_GetError(), data->window);
  }
  SDL_FreeSurface(sprites_img);
  SDL_SetRenderDrawColor(data->renderer, 90, 90, 90, 255);
  SDL_RenderClear(data->renderer);
  data->texture = sprite_texture;
  /*
  ** important, use this to apply modification on last textures
  ** placed on the renderer
  */
  SDL_SetRenderTarget(data->renderer, NULL);
  return (NULL);
}

/*
void function_test(t_game_info game_info, t_base_map base_map) {
  int i;
  int convert_x;
  int convert_y;

  for (i = 0; i < 4; i++) {
    if (game_info->players[i].alive) {
      convert_x = walk_X_into_pixels(game_info->players[i].x_pos);
      convert_y = walk_Y_into_pixels(game_info->players[i].y_pos);
      if (convert_x == base_map->players[i].x && convert_y == base_map->players[i].y) {
	continue;
      } else if (convert_x != base_map->players[i].x) {
	if (game_info->players[i].current_dir == bomb_d) {
	  move_player_down(base_map,i);
	} else {
	  move_player_up(base_map,i);
	}
      } else if (convert_y != base_map->players[i].y) {
	if (game_info->players[i].current_dir == bomb_l) {
	  move_player_left(base_map, i);
	} else {
	  move_player_right(base_map, i);
	}
      }

    } else if (game_info->players[i].dying) {
      //what to do here ? anim the dying mother fucker
    }
  }
}

void	update_destroyable_stuffs(t_game_info game_info){
  int	i;
  int	j;

  for (i = 0; i < 14; i++) {
    for (j = 0; i < 15; i++) {
      if (game_info->map_destroyable[i][j].wall_destroyable) {
	draw_destroyable_wall(game_info);
      }
      }
    }
  }
}

int walk_Y_into_pixels(int value) {
  int first_step_X =  (I_BEGIN + 1) * 48;
  value *= first_step_X;
  return (value);
}

int walk_X_into_pixels(int value) {
  int first_step_Y = ((J_BEGIN + 1) * 48) - 36;
  value *= first_step_Y;
  return (value);
}
*/
