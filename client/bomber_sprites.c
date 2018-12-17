#include "enum.h"
/** SDL.h includes in bomber_sprites.h **/
#include "bomber_sprites.h"

const  SDL_Rect	blue_sprites[5][4]  = initBlueBomberSprites();
const  SDL_Rect black_sprites[5][4] = initBlackBomberSprites();
const  SDL_Rect	red_sprites[5][4]   = initRedBomberSprites();
const  SDL_Rect white_sprites[5][4] = initWhiteBomberSprites();
const  SDL_Rect bomb_sprites[3][3]  = initBombSprites();

SDL_Rect getBlueSprites()
{
    return blue_sprites;
}

SDL_Rect getBlackSprites()
{
    return black_sprites;
}

SDL_Rect getRedSprites()
{
    return red_sprites;
}

SDL_Rect getWhiteSprites()
{
    return white_sprites;
}

SDL_Rect getBombSprites()
{
    return bomb_sprites
}


SDL_Rect initBlueBomberSprites()
{
    SDL_Rect bomber_sprites[5][4];

    bomber_sprites[bomber_d][not_move] = init_rect(70, 92, 16, 24);
    bomber_sprites[bomber_d][move_l] = init_rect(52, 92, 16, 24);
    bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    bomber_sprites[bomber_d][move_r] = init_rect(88, 92, 16, 24);
    bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    bomber_sprites[bomber_l][move_l] = init_rect(106, 92, 16, 24);
    bomber_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
    bomber_sprites[bomber_l][move_r] = init_rect(143, 92, 16, 24);
    bomber_sprites[bomber_r][not_move] = init_rect(179, 92, 16, 24);
    bomber_sprites[bomber_r][move_l] = init_rect(160, 92, 16, 24);
    bomber_sprites[bomber_r][transit_move] = init_rect(179, 92, 16, 24);
    bomber_sprites[bomber_r][move_r] = init_rect(197, 92, 16, 24);
    bomber_sprites[bomber_u][not_move] = init_rect(237, 92, 16, 24);
    bomber_sprites[bomber_u][move_l] = init_rect(219, 92, 16, 24);
    bomber_sprites[bomber_u][transit_move] = init_rect(237, 92, 16, 24);
    bomber_sprites[bomber_u][move_r] = init_rect(255, 92, 16, 24);
    bomber_sprites[die][0] = init_rect(345, 92, 16, 24);
    bomber_sprites[die][1] = init_rect(361, 92, 16, 24);
    bomber_sprites[die][2] = init_rect(395, 92, 16, 24);

    return bomber_sprites;
}

SDL_Rect initBlackBomberSprites()
{
    SDL_Rect bomber_sprites[5][4];

    bomber_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
    bomber_sprites[bomber_d][move_l] = init_rect(52, 66, 16, 24);
    bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    bomber_sprites[bomber_d][move_r] = init_rect(88, 66, 16, 24);
    bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    bomber_sprites[bomber_l][move_l] = init_rect(106, 66, 16, 24);
    bomber_sprites[bomber_l][transit_move] = init_rect(124, 66, 16, 24);
    bomber_sprites[bomber_l][move_r] = init_rect(143, 66, 16, 24);
    bomber_sprites[bomber_r][not_move] = init_rect(179, 66, 16, 24);
    bomber_sprites[bomber_r][move_l] = init_rect(160, 66, 16, 24);
    bomber_sprites[bomber_r][transit_move] = init_rect(179, 66, 16, 24);
    bomber_sprites[bomber_r][move_r] = init_rect(197, 66, 16, 24);
    bomber_sprites[bomber_u][not_move] = init_rect(237, 66, 16, 24);
    bomber_sprites[bomber_u][move_l] = init_rect(219, 66, 16, 24);
    bomber_sprites[bomber_u][transit_move] = init_rect(237, 66, 16, 24);
    bomber_sprites[bomber_u][move_r] = init_rect(255, 66, 16, 24);
    bomber_sprites[die][0] = init_rect(345, 66, 16, 24);
    bomber_sprites[die][1] = init_rect(361, 66, 16, 24);
    bomber_sprites[die][2] = init_rect(395, 66, 16, 24);
    return bomber_sprites;
}

SDL_Rect initRedBomberSprites()
{
    SDL_Rect bomber_sprites[5][4];

    bomber_sprites[bomber_d][not_move] = init_rect(70, 120, 16, 24);
    bomber_sprites[bomber_d][move_l] = init_rect(52, 120, 16, 24);
    bomber_sprites[bomber_d][transit_move] = init_rect(70, 120, 16, 24);
    bomber_sprites[bomber_d][move_r] = init_rect(88, 120, 16, 24);
    bomber_sprites[bomber_l][not_move] = init_rect(124, 120, 16, 24);
    bomber_sprites[bomber_l][move_l] = init_rect(106, 120, 16, 24);
    bomber_sprites[bomber_l][transit_move] = init_rect(124, 120, 16, 24);
    bomber_sprites[bomber_l][move_r] = init_rect(143, 120, 16, 24);
    bomber_sprites[bomber_r][not_move] = init_rect(179, 120, 16, 24);
    bomber_sprites[bomber_r][move_l] = init_rect(160, 120, 16, 24);
    bomber_sprites[bomber_r][transit_move] = init_rect(179, 120, 16, 24);
    bomber_sprites[bomber_r][move_r] = init_rect(197, 120, 16, 24);
    bomber_sprites[bomber_u][not_move] = init_rect(237, 120, 16, 24);
    bomber_sprites[bomber_u][move_l] = init_rect(219, 120, 16, 24);
    bomber_sprites[bomber_u][transit_move] = init_rect(237, 120, 16, 24);
    bomber_sprites[bomber_u][move_r] = init_rect(255, 120, 16, 24);
    bomber_sprites[die][0] = init_rect(345, 120, 16, 24);
    bomber_sprites[die][1] = init_rect(361, 120, 16, 24);
    bomber_sprites[die][2] = init_rect(395, 120, 16, 24);

    return bomber_sprites;
}

SDL_Rect initWhiteBomberSprites()
{
    SDL_Rect bomber_sprites[5][4];

    bomber_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
    bomber_sprites[bomber_d][move_l] = init_rect(52, 38, 16, 24);
    bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    bomber_sprites[bomber_d][move_r] = init_rect(88, 38, 16, 24);
    bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    bomber_sprites[bomber_l][move_l] = init_rect(106, 38, 16, 24);
    bomber_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
    bomber_sprites[bomber_l][move_r] = init_rect(143, 38, 16, 24);
    bomber_sprites[bomber_r][not_move] = init_rect(179, 38, 16, 24);
    bomber_sprites[bomber_r][move_l] = init_rect(160, 38, 16, 24);
    bomber_sprites[bomber_r][transit_move] = init_rect(179, 38, 16, 24);
    bomber_sprites[bomber_r][move_r] = init_rect(197, 38, 16, 24);
    bomber_sprites[bomber_u][not_move] = init_rect(237, 38, 16, 24);
    bomber_sprites[bomber_u][move_l] = init_rect(219, 38, 16, 24);
    bomber_sprites[bomber_u][transit_move] = init_rect(237, 38, 16, 24);
    bomber_sprites[bomber_u][move_r] = init_rect(255, 38, 16, 24);
    bomber_sprites[die][0] = init_rect(345, 38, 16, 24);
    bomber_sprites[die][1] = init_rect(361, 38, 16, 24);
    bomber_sprites[die][2] = init_rect(395, 38, 16, 24);

    return bomber_sprites;
}

SDL_Rect initBombSprites()
{
    SDL_Rect new_bomb_sprites[3][3];

    bomb_sprites[bomb][bomb_s] = init_rect(17, 255, 16, 17);
    bomb_sprites[bomb][bomb_m] = init_rect(33, 255, 16, 17);
    bomb_sprites[bomb][bomb_l] = init_rect(50, 38, 16, 17);

    return new_bomb_sprites
}
