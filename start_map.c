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

int		start_map(t_sdl *sdl, int socket)
{
  int		quit;
  SDL_Event	event;
  t_data	*data;
  t_thread	*struct_thread;
  pthread_t	listen_server_thread;

  quit = 0;
  if ((data = malloc(sizeof(*data))) == NULL) {
    return (0);
  }
  data->renderer = sdl->renderer;
  data->window = sdl->window;
  if ((struct_thread = malloc(sizeof(t_thread))) == NULL) {
    return 0;
  }
  struct_thread->socket = socket;
  struct_thread->data = data;
  init_sprites_sheet((void *)data);
  initSprites();
  if (!draw_fixed_map((void *)data)) {
    return (0);
  }
  SDL_SetRenderTarget(data->renderer, NULL);
  SDL_RenderPresent(data->renderer);
  SDL_RenderClear(data->renderer);
  printf("\nbefore create thread\n");
  if (pthread_create(&listen_server_thread, NULL, listen_server, struct_thread) != 0) {
    printf("pthread_create listen_server failed\n");
    quit = 1;
  } else {
    printf("\nthread created\n");
  }
  send_request(socket, GIVE_PLAYERS);
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
		break;
	    case SDL_KEYDOWN:
	      switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		  send_request(socket, MOVE_UP);
		  break;
		case SDLK_LEFT:
		  send_request(socket, MOVE_LEFT);
		  break;
		case SDLK_RIGHT:
		  send_request(socket, MOVE_RIGHT);
		  break;
		case SDLK_DOWN:
		  send_request(socket, MOVE_DOWN);
		  break;
		case SDLK_SPACE:
		  send_request(socket, PLACE_BOMB);
		  break;
		}
	    }
	}
    }
  pthread_cancel(listen_server_thread);
  SDL_DestroyTexture(data->texture);
  free(data);
  return (0);
}

void		*init_sprites_sheet(void *arg)
{
  SDL_Texture	*sprite_texture;
  SDL_Surface	*sprites_img;
  t_data	*data = (t_data *)arg;

  sprites_img = NULL;
  sprite_texture = NULL;
  IMG_Init(IMG_INIT_PNG);

  #ifdef linux
    sprites_img = IMG_Load("/usr/share/bomberman/ressources/bombermanSprite.PNG");
  #else
    sprites_img = IMG_Load("./ressources/bombermanSprite.PNG");
  #endif

  if (!sprites_img)
  {
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(),
                             data->window);
  }

  //we create the image as a texture to insert it in renderer
  sprite_texture = SDL_CreateTextureFromSurface(data->renderer,
                                                sprites_img);
  if (!sprite_texture) {
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
