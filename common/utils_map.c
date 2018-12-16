/*
** draw_base_map.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/base_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:31:13 2018 MASERA Mathieu
** Last update Wed Jul  4 09:31:14 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "request.h"
#include "player.h"
#include "sdl.h"
#include "base_map.h"
#include "game_info.h"

void *draw_map_loop(int i, int j) {
    int code;

    if (j == J_BEGIN || j == J_BEGIN + 12 || i == I_BEGIN || i == I_BEGIN + 14) {
        code = WALL;
    } else if (j == J_BEGIN + 1 || (j % 2 != J_BEGIN % 2 && i % 2 == I_BEGIN % 2)) {
        code = FREE_SLOT;
    } else if (i % 2 != I_BEGIN % 2) {
        code = FREE_SLOT;
    } else if (i % 2 == I_BEGIN % 2) {
        code = WALL;
    } else {
        code = 500;
    }

    return code;
}

void *render_error(char *title, char *message) {
    SDL_ShowSimpleMessageBox(0, title, message, data->window);
}
