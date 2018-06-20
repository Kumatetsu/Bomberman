#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "base_map.h"

int		start_map(t_sdl *sdl)
{
  int		quit;
  SDL_Event	event;
  t_data	*data;

  quit = 0;
  data = malloc(sizeof(*data));
  data->renderer = sdl->renderer;
  data->window = sdl->window;
  init_sprites_sheet((void*)data);
  draw_all((void*)data);
  SDL_SetRenderTarget(data->renderer, NULL);
  SDL_RenderPresent(data->renderer);
  SDL_RenderClear(data->renderer);
  while(!quit)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  quit = 1;
	  break;
	case SDL_KEYUP:
	  {
	    SDL_RenderClear(data->renderer);
	    rebuild_map((void*)data);
	    move_player_stop((void*)data);
	    break;
	  }
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym) {
	  case SDLK_UP:
	    SDL_RenderClear(data->renderer);
	    rebuild_map((void*)data);
	    move_player_up((void*)data);
	    break;
	  case SDLK_LEFT:
	    SDL_RenderClear(data->renderer);
	    rebuild_map((void*)data);
	    move_player_left((void*)data);
	    break;
	  case SDLK_RIGHT:
	    SDL_RenderClear(data->renderer);
	    rebuild_map((void*)data);
	    move_player_right((void*)data);
	    break;
	  case SDLK_DOWN:
	    SDL_RenderClear(data->renderer);
	    rebuild_map((void*)data);
	    move_player_down((void*)data);
	    break;
	  }
	}
      	  SDL_RenderPresent(data->renderer);
 	  SDL_SetRenderTarget(data->renderer, NULL);
    } 
    
  SDL_DestroyTexture(data->texture);
  free(data);
  return 0;
}

void		*init_sprites_sheet(void *arg) {
  SDL_Texture	*sprite_texture;
  SDL_Surface	*sprites_img;

  t_data *data = (t_data*)arg;
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


