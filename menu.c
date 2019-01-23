/*
** menu.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 00:13:56 2018 MASERA Mathieu
** Last update Wed Jul  4 00:28:14 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include "sdl.h"
#include "client.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC
#endif
#include <pthread.h>


/**
 * Init le menu permettant de choisir de se connecter à un server
 * ou de créer un server
**/

void		main_menu(t_sdl *sdl)
{
  int		quit = 0;
  int		x;
  int   	y;
  SDL_Event	event_queue;
  SDL_Rect      join_position = {200, 300, 400, 60};
  SDL_Rect      create_position = {200, 400, 400, 60};
  pthread_t	server_thread;

  while(!quit) {
    while(SDL_PollEvent(&event_queue)) {
      switch(event_queue.type){
      case SDL_QUIT:
	quit = 1;
	break;
      case SDL_MOUSEBUTTONDOWN:
	x = event_queue.button.x;
	y = event_queue.button.y;

	if (( x > join_position.x ) && ( x < join_position.x + join_position.w ) && ( y > join_position.y ) && ( y < join_position.y + join_position.h ) ) {
	  init_client(sdl);
	  printf("join button pressed");
	}
	if (( x > create_position.x ) && ( x < create_position.x + create_position.w ) && ( y > create_position.y ) && ( y < create_position.y + create_position.h ) ) {
	  printf("server button pressed");
	  if (pthread_create(&server_thread, NULL, init_server, NULL) == -1)
	    return;
	}
	break;
      }
    }

    SDL_RenderClear(sdl->renderer);
    SDL_RenderCopy(sdl->renderer, sdl->menu_background, NULL, NULL);
    SDL_RenderCopy(sdl->renderer, sdl->join_game, NULL, &join_position);
    SDL_RenderCopy(sdl->renderer, sdl->create_game, NULL, &create_position);
    SDL_RenderPresent(sdl->renderer);
  }
  pthread_cancel(server_thread);
  return;
}
