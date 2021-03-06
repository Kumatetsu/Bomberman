#include "enum.h"
/** SDL.h includes in bomber_sprites.h **/
#include "bomber_sprites.h"
#include "map.h"
#include "base_map_manager.h"
#include "constant.h"

/**
 * Contain all sprites for bombers and bomb
 **/
static  SDL_Rect blue_sprites[5][4];
static  SDL_Rect black_sprites[5][4];
static  SDL_Rect red_sprites[5][4];
static  SDL_Rect white_sprites[5][4];
static  SDL_Rect bomb_sprites[3][3];
static	SDL_Rect explosion_sprites[5];
static	SDL_Rect explosion_sprite;

/**
 * Init all statics by launching all init functions
 **/
void initSprites()
{
  initBomberSprites(Y_WHITE_B);
  initBomberSprites(Y_BLACK_B);
  initBomberSprites(Y_BLUE_B);
  initBomberSprites(Y_RED_B);
  initBombSprites();
  initExplosionSprites();
}

/**
 * Get your bomber sprites (depend on num_player [0 -> 3])
 **/
SDL_Rect getBomberSprites(int num_player, int dir, int action)
{
  SDL_Rect default_rect = {0};

  switch (num_player)
    {
    case 0:
      return getWhiteSprites(dir, action);
      break;
    case 1:
      return getBlackSprites(dir, action);
      break;
    case 2:
      return getBlueSprites(dir, action);
      break;
    case 3:
      return getRedSprites(dir, action);
      break;
    default:
      return default_rect;
      break;
    }
}

SDL_Rect getBlueSprites(int dir, int action)
{
  return (blue_sprites[dir][action]);
}

SDL_Rect getBlackSprites(int dir, int action)
{
  return (black_sprites[dir][action]);
}

SDL_Rect getRedSprites(int dir, int action)
{
  return (red_sprites[dir][action]);
}

SDL_Rect getWhiteSprites(int dir, int action)
{
  return (white_sprites[dir][action]);
}

SDL_Rect getBombSprites(int type)
{
  return (bomb_sprites[bomb][type]);
}

SDL_Rect getExplosionSprites(int type)
{
  return (explosion_sprites[type]);
}

void		initBomberSprites(int y)
{
  SDL_Rect	(*container)[5][4];

  switch(y)
    {
    case Y_BLUE_B:
      container = &blue_sprites;
      break;
    case Y_BLACK_B:
      container = &black_sprites;
      break;
    case Y_RED_B:
      container = &red_sprites;
      break;
    case Y_WHITE_B:
      container = &white_sprites;
      break;
    }

  (*container)[bomber_u][move_r] = init_rect(255, y, 16, 24);
  (*container)[bomber_u][not_move] = init_rect(237, y, 16, 24);
  (*container)[bomber_u][transit_move] = init_rect(237, y, 16, 24);
  (*container)[bomber_u][move_l] = init_rect(219, y, 16, 24);
  (*container)[bomber_d][not_move] = init_rect(70, y, 16, 24);
  (*container)[bomber_d][move_l] = init_rect(52, y, 16, 24);
  (*container)[bomber_d][transit_move] = init_rect(70, y, 16, 24);
  (*container)[bomber_d][move_r] = init_rect(88, y, 16, 24);
  (*container)[bomber_l][not_move] = init_rect(124, 38, 16, 24);
  (*container)[bomber_l][move_l] = init_rect(106, y, 16, 24);
  (*container)[bomber_l][transit_move] = init_rect(124, y, 16, 24);
  (*container)[bomber_l][move_r] = init_rect(142, y, 16, 24);
  (*container)[bomber_r][not_move] = init_rect(179, y, 16, 24);
  (*container)[bomber_r][move_l] = init_rect(161, y, 16, 24);
  (*container)[bomber_r][transit_move] = init_rect(179, y, 16, 24);
  (*container)[bomber_r][move_r] = init_rect(197, y, 16, 24);
  (*container)[bomber_u][move_l] = init_rect(219, y, 16, 24);

  (*container)[die][0] = init_rect(345, y, 16, 24);
  (*container)[die][1] = init_rect(361, y, 16, 24);
  (*container)[die][2] = init_rect(395, y, 16, 24);
}

void initBombSprites()
{
  bomb_sprites[bomb][bomb_s] = init_rect(17, Y_BOMB, 16, 17);
  bomb_sprites[bomb][bomb_m] = init_rect(33, Y_BOMB, 16, 17);
  bomb_sprites[bomb][bomb_l] = init_rect(50, Y_BOMB, 16, 17);
}

void initExplosionSprites()
{
  explosion_sprites[0] = init_rect(153, Y_FIRE, 78, 80);
  explosion_sprites[1] = init_rect(235, Y_FIRE, 80, 85);
  explosion_sprites[2] = init_rect(318, Y_FIRE, 80, 85);
  explosion_sprites[3] = init_rect(403, Y_FIRE, 80, 85);
  explosion_sprites[4] = init_rect(487, Y_FIRE, 80, 85);
}

int	getExplosionX(int index)
{
  switch(index)
    {
    case 1:
      return (XFIRE1);
    case 2:
      return (XFIRE2);
    case 3:
      return (XFIRE3);
    case 4:
      return (XFIRE4);
    case 5:
      return (XFIRE5);
    default:
      return (XFIRE1);
    }
}

SDL_Rect	getCenterExplosion(int type)
{
  int		x;

  x = getExplosionX(type);
  explosion_sprite = init_rect(x + 32, Y_FIRE + 36, 16, 16);
  return (explosion_sprite);
}

SDL_Rect	getExplosionSprite(int x,
				   int y,
				   int width,
				   int height)
{
  explosion_sprite = init_rect(x, y, width, height);
  return (explosion_sprite);
}
