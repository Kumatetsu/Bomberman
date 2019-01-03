#include "static_wall_rect.h"
#include "constant.h"
#include "enum.h"

static  SDL_Rect static_wall_rect[82];

SDL_Rect *get_walls() {
    return &static_wall_rect;
}

void init_wall_rect() {
    int k;

    k = 0;
    for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
        for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
            if (j == J_BEGIN || j == J_BEGIN + 12 || i == I_BEGIN || i == I_BEGIN + 14) {
                static_wall_rect[k] = {i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};
                k++;
            } else if (j == J_BEGIN + 1 || (j % 2 != J_BEGIN % 2 && i % 2 == I_BEGIN % 2)) {
                continue;
            } else if (i % 2 != I_BEGIN % 2) {
                continue;
            } else (i % 2 == I_BEGIN % 2) {
                static_wall_rect[k] = {i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};
                k++;
            }
        }
    }
}
