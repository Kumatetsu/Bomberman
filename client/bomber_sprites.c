#include "enum.h"
/** SDL.h includes in bomber_sprites.h **/
#include "bomber_sprites.h"
#include "map.h"
#include "base_map_manager.h"

/**
 * Contain all sprites for bombers and bomb
**/
static  SDL_Rect blue_sprites[5][4];
static  SDL_Rect black_sprites[5][4];
static  SDL_Rect red_sprites[5][4];
static  SDL_Rect white_sprites[5][4];
static  SDL_Rect bomb_sprites[3][3];

/**
 * Init all statics by launching all init functions
**/
void initSprites()
{
    initBlueBomberSprites();
    initBlackBomberSprites();
    initRedBomberSprites();
    initWhiteBomberSprites();
    initBombSprites();
}

/**
 * Get your bomber sprites (depend on num_player [0 -> 3])
**/
SDL_Rect getBomberSprites(int num_player)
{
    SDL_Rect default_rect;
    /**
     * TODO: Get la game info pour envoyer les bonnes datas dans le get sprites
    **/
    switch (num_player)
    {
        case 0:
            return getWhiteSprites(1, 1);
            break;
        case 1:
            return getBlackSprites(1, 1);
            break;
        case 2:
            return getBlueSprites(1, 1);
            break;
        case 3:
            return getRedSprites(1, 1);
            break;
        default:
            return default_rect;
            break;
    }
}

SDL_Rect getBlueSprites(int dir, int action)
{
    return blue_sprites[dir][action];
}

SDL_Rect getBlackSprites(int dir, int action)
{
    return black_sprites[dir][action];
}

SDL_Rect getRedSprites(int dir, int action)
{
    return red_sprites[dir][action];
}

SDL_Rect getWhiteSprites(int dir, int action)
{
    return white_sprites[dir][action];
}

SDL_Rect getBombSprites(int type)
{
    return bomb_sprites[bomb][type];
}


void initBlueBomberSprites()
{
    blue_sprites[bomber_d][not_move] = init_rect(70, 92, 16, 24);
    blue_sprites[bomber_d][move_l] = init_rect(52, 92, 16, 24);
    blue_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    blue_sprites[bomber_d][move_r] = init_rect(88, 92, 16, 24);
    blue_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    blue_sprites[bomber_l][move_l] = init_rect(106, 92, 16, 24);
    blue_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
    blue_sprites[bomber_l][move_r] = init_rect(143, 92, 16, 24);
    blue_sprites[bomber_r][not_move] = init_rect(179, 92, 16, 24);
    blue_sprites[bomber_r][move_l] = init_rect(160, 92, 16, 24);
    blue_sprites[bomber_r][transit_move] = init_rect(179, 92, 16, 24);
    blue_sprites[bomber_r][move_r] = init_rect(197, 92, 16, 24);
    blue_sprites[bomber_u][not_move] = init_rect(237, 92, 16, 24);
    blue_sprites[bomber_u][move_l] = init_rect(219, 92, 16, 24);
    blue_sprites[bomber_u][transit_move] = init_rect(237, 92, 16, 24);
    blue_sprites[bomber_u][move_r] = init_rect(255, 92, 16, 24);
    blue_sprites[die][0] = init_rect(345, 92, 16, 24);
    blue_sprites[die][1] = init_rect(361, 92, 16, 24);
    blue_sprites[die][2] = init_rect(395, 92, 16, 24);
}

void initBlackBomberSprites()
{
    black_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
    black_sprites[bomber_d][move_l] = init_rect(52, 66, 16, 24);
    black_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    black_sprites[bomber_d][move_r] = init_rect(88, 66, 16, 24);
    black_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    black_sprites[bomber_l][move_l] = init_rect(106, 66, 16, 24);
    black_sprites[bomber_l][transit_move] = init_rect(124, 66, 16, 24);
    black_sprites[bomber_l][move_r] = init_rect(143, 66, 16, 24);
    black_sprites[bomber_r][not_move] = init_rect(179, 66, 16, 24);
    black_sprites[bomber_r][move_l] = init_rect(160, 66, 16, 24);
    black_sprites[bomber_r][transit_move] = init_rect(179, 66, 16, 24);
    black_sprites[bomber_r][move_r] = init_rect(197, 66, 16, 24);
    black_sprites[bomber_u][not_move] = init_rect(237, 66, 16, 24);
    black_sprites[bomber_u][move_l] = init_rect(219, 66, 16, 24);
    black_sprites[bomber_u][transit_move] = init_rect(237, 66, 16, 24);
    black_sprites[bomber_u][move_r] = init_rect(255, 66, 16, 24);
    black_sprites[die][0] = init_rect(345, 66, 16, 24);
    black_sprites[die][1] = init_rect(361, 66, 16, 24);
    black_sprites[die][2] = init_rect(395, 66, 16, 24);
}

void initRedBomberSprites()
{
    red_sprites[bomber_d][not_move] = init_rect(70, 120, 16, 24);
    red_sprites[bomber_d][move_l] = init_rect(52, 120, 16, 24);
    red_sprites[bomber_d][transit_move] = init_rect(70, 120, 16, 24);
    red_sprites[bomber_d][move_r] = init_rect(88, 120, 16, 24);
    red_sprites[bomber_l][not_move] = init_rect(124, 120, 16, 24);
    red_sprites[bomber_l][move_l] = init_rect(106, 120, 16, 24);
    red_sprites[bomber_l][transit_move] = init_rect(124, 120, 16, 24);
    red_sprites[bomber_l][move_r] = init_rect(143, 120, 16, 24);
    red_sprites[bomber_r][not_move] = init_rect(179, 120, 16, 24);
    red_sprites[bomber_r][move_l] = init_rect(160, 120, 16, 24);
    red_sprites[bomber_r][transit_move] = init_rect(179, 120, 16, 24);
    red_sprites[bomber_r][move_r] = init_rect(197, 120, 16, 24);
    red_sprites[bomber_u][not_move] = init_rect(237, 120, 16, 24);
    red_sprites[bomber_u][move_l] = init_rect(219, 120, 16, 24);
    red_sprites[bomber_u][transit_move] = init_rect(237, 120, 16, 24);
    red_sprites[bomber_u][move_r] = init_rect(255, 120, 16, 24);
    red_sprites[die][0] = init_rect(345, 120, 16, 24);
    red_sprites[die][1] = init_rect(361, 120, 16, 24);
    red_sprites[die][2] = init_rect(395, 120, 16, 24);
}

void initWhiteBomberSprites()
{
    white_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
    white_sprites[bomber_d][move_l] = init_rect(52, 38, 16, 24);
    white_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
    white_sprites[bomber_d][move_r] = init_rect(88, 38, 16, 24);
    white_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
    white_sprites[bomber_l][move_l] = init_rect(106, 38, 16, 24);
    white_sprites[bomber_l][transit_move] = init_rect(124, 38, 16, 24);
    white_sprites[bomber_l][move_r] = init_rect(143, 38, 16, 24);
    white_sprites[bomber_r][not_move] = init_rect(179, 38, 16, 24);
    white_sprites[bomber_r][move_l] = init_rect(160, 38, 16, 24);
    white_sprites[bomber_r][transit_move] = init_rect(179, 38, 16, 24);
    white_sprites[bomber_r][move_r] = init_rect(197, 38, 16, 24);
    white_sprites[bomber_u][not_move] = init_rect(237, 38, 16, 24);
    white_sprites[bomber_u][move_l] = init_rect(219, 38, 16, 24);
    white_sprites[bomber_u][transit_move] = init_rect(237, 38, 16, 24);
    white_sprites[bomber_u][move_r] = init_rect(255, 38, 16, 24);
    white_sprites[die][0] = init_rect(345, 38, 16, 24);
    white_sprites[die][1] = init_rect(361, 38, 16, 24);
    white_sprites[die][2] = init_rect(395, 38, 16, 24);
}

void initBombSprites()
{
    bomb_sprites[bomb][bomb_s] = init_rect(17, 255, 16, 17);
    bomb_sprites[bomb][bomb_m] = init_rect(33, 255, 16, 17);
    bomb_sprites[bomb][bomb_l] = init_rect(50, 38, 16, 17);
}
