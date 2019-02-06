/*
** main.c for Bomberman in /Users/kumatetsu/projet-etna/DVC4/Bomberman/Bomberman
**
** Made by BILLAUD Jean
** Login   <billau_j@etna-alternance.net>
**
** Started on  Tue Jun 26 17:26:19 2018 BILLAUD Jean
** Last update Mon Jul  2 18:46:25 2018 BILLAUD Jean
*/

#include <stdlib.h>
#include <stdio.h>
#include "enum.h"
#include "sdl.h"
#include "map.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "menu.h"
#include "player.h"
#include "base_map_manager.h"

int main (int argc, char *argv[])
{
	//made on purpose for windows errors on compilation
	argc = argc;
	argv = argv;
#ifdef _WIN32
	int retWSADATA;
	WSADATA WSAData;

	if ((retWSADATA = WSAStartup(MAKEWORD(2, 2), &WSAData)) != 0) {
		printf("main.c : WSAStartup() failed with error %d\n", retWSADATA);
	//	WSACleanup();
		return (1);
	}
	if (LOBYTE(WSAData.wVersion) != 2 || HIBYTE(WSAData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
#endif // _WIN32
	
	t_sdl *sdl;
  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG);
  TTF_Init();

  sdl = init_sdl();
  sdl = init_window(sdl);
  sdl = init_fronts(sdl);

  //comment maiemacs n to see start_map working ;)
  main_menu(sdl);
  SDL_DestroyTexture(sdl->menu_background);
  SDL_DestroyTexture(sdl->white_back);
  SDL_DestroyTexture(sdl->join_game);
  SDL_DestroyTexture(sdl->create_game);
  SDL_DestroyTexture(sdl->server_welcome);
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  free(sdl);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
#if _WIN32
  printf("main.c : WSACleanup\n");
  WSACleanup();
#endif
  //FOR DEV PURPOSE ONLY
  return 0;
}
