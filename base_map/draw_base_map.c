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
#include "server.h"
#include "player.h"
#include "sdl.h"
#include "base_map.h"
#include "game_info.h"

void *draw_map_model(void *arg)
{
    int i, j, height, width, error, element_type;

    t_data *data = (t_data *) arg;
    error = 0;
    height = 1;
    SDL_Rect ground_value;
    texture_type texture_value;
    SDL_Rect wall_src_rect = {71, 175, 16, 16};
    SDL_Rect ground_src_rect = {122, 175, 16, 16};
    SDL_Rect ground_shadowed_rect = {105, 175, 16, 16};

    // hauteur
    for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
        width = 0;
        // largeur
        for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
            SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};

            element_type = draw_map_loop(i, j);
            if (element_type == WALL) {
                ground_value = wall_src_rect;
                texture_value = wall;
            }
            else if (element_type == FREE_SLOT) {
                ground_value = ground_src_rect;
                texture_value = ground_shadowed;
            }
            else if (element_type == FREE_SLOT_SHADOW) {
                ground_value = ground_shadowed_rect;
                texture_value = ground_shadowed;
            }
            else {
                error = 1;
                SDL_ShowSimpleMessageBox(0, "adding texture in renderer error", SDL_GetError(), data->window);
                break;
            }

            // TODO: separate rendering and map building
            error = SDL_RenderCopy(data->renderer, data->texture, &ground_value, &dest_rect);
            data->array_map[height][width] = init_t_map(ground_value, dest_rect, texture_value);

            if (error < 0) {
                SDL_ShowSimpleMessageBox(0, "adding texture in renderer error",
                                         SDL_GetError(), data->window);
                break;
            }
            width++;
        }
        if (error < 0)
            break;
        height++;
    }
    if (error < 0)
        return (NULL);
    return ((void *) data);
}

void *draw_timer(void *arg)
{
    int error;

    error = 0;
    t_data *data = (t_data *) arg;
    SDL_Rect timer_panel_rect = {413, 37, 32, 14};
    SDL_Rect dest_rect_score = {0, 0, WINDOW_W, J_BEGIN * PIXEL_SIZE};
    SDL_Rect dest_rect_timer = {(WINDOW_W / 2) - ((timer_panel_rect.w / 2) * 5),
                                (dest_rect_score.h / 2) -
                                    ((timer_panel_rect.h / 2) * 5),
                                timer_panel_rect.w * 5,
                                timer_panel_rect.h * 5};
    error = SDL_RenderCopy(data->renderer, data->texture,
                           &timer_panel_rect, &dest_rect_timer);
    data->array_map[0][1] = init_t_map(timer_panel_rect, dest_rect_timer,
                                       timer);
    if (error < 0)
        SDL_ShowSimpleMessageBox(0, "drawing Timer Failed",
                                 SDL_GetError(), data->window);
    return (NULL);
}

void *draw_pannel(void *arg)
{
    int error;

    error = 0;
    t_data *data = (t_data *) arg;
    SDL_Rect score_panel_rect = {414, 175, 256, 32};
    SDL_Rect dest_rect_score = {0, 0, WINDOW_W, J_BEGIN * PIXEL_SIZE};
    error = SDL_RenderCopy(data->renderer, data->texture,
                           &score_panel_rect, &dest_rect_score);
    data->array_map[0][0] = init_t_map(score_panel_rect, dest_rect_score,
                                       pannel);
    if (error < 0)
        SDL_ShowSimpleMessageBox(0, "drawing Score Tab Failed",
                                 SDL_GetError(), data->window);
    return (NULL);
}
