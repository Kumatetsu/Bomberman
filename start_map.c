/*
** start_map.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:30:11 2018 MASERA Mathieu
** Last update Wed Jul  4 09:30:12 2018 MASERA Mathieu
*/

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC
#endif

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
// sur!
#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "map.h"
#include "client_request.h"
#include "player_info.h"
#include "server.h"
#include "game_info.h"
#include "client_receive.h"
#include "client_request.h"
#include "data.h"
#include "thread.h"
#include "base_map_manager.h"
#include "start_map.h"
#include "bomber_sprites.h"

int		start_map(t_sdl *sdl, int socket, t_player_request *cr)
{
  int		quit;
  SDL_Event	event;
  t_data	*data;
  t_thread	*struct_thread;
  pthread_t	listen_server_thread;

  quit = 0;
  if ((data = malloc(sizeof(*data))) == NULL)
    return 0;
  data->renderer = sdl->renderer;
  data->window = sdl->window;
  if ((struct_thread = malloc(sizeof(t_thread))) == NULL)
    return 0;
  struct_thread->socket = socket;
  struct_thread->data = data;
  init_sprites_sheet((void *)data);
  initSprites();
  if (!draw_fixed_map((void *)data))
    return (0);
  SDL_SetRenderTarget(data->renderer, NULL);
  SDL_RenderPresent(data->renderer);
  SDL_RenderClear(data->renderer);
  printf("\nbefore create thread\n");
  if (pthread_create(&listen_server_thread, NULL, listen_server, struct_thread))
    quit = 1;
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
        // SDL_RenderClear(data->renderer);
        // rebuild_map((void *)data);
        // move_player_stop((void *)data);
        // draw_all(data);
        // SDL_RenderPresent(data->renderer);
        // SDL_SetRenderTarget(data->renderer, NULL);
        break;
      }
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
          //SDL_RenderClear(data->renderer);
          //rebuild_map((void *)data);
          cr->command = MOVE_UP;
          send_request(socket, cr);
          break;
        case SDLK_LEFT:
          //SDL_RenderClear(data->renderer);
          //rebuild_map((void *)data);
          cr->command = MOVE_LEFT;
          send_request(socket, cr);
          break;
        case SDLK_RIGHT:
          //SDL_RenderClear(data->renderer);
          //rebuild_map((void *)data);
          cr->command = MOVE_RIGHT;
          send_request(socket, cr);
          break;
        case SDLK_DOWN:
          //SDL_RenderClear(data->renderer);
          //rebuild_map((void *)data);
          cr->command = MOVE_DOWN;
          send_request(socket, cr);
          break;
        case SDLK_SPACE:
	  printf("\nI WANT A BOMB\n");
	  cr->command = PLACE_BOMB;
	  printf("\nplayer request: %d\n", cr->command);
	  send_request(socket, cr);
          break;
        }
      }
    }
  }
  pthread_cancel(listen_server_thread);
  SDL_DestroyTexture(data->texture);
  free(data);
  return 0;
}

void		*init_sprites_sheet(void *arg)
{
  SDL_Texture	*sprite_texture;
  SDL_Surface	*sprites_img;
  t_data	*data = (t_data *)arg;

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
