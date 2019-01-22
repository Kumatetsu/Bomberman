#ifndef _BOMBER_SPRITES_H_
#define _BOMBER_SPRITES_H_

#include "sdl.h"
/**
 * GETTERS
**/
SDL_Rect getBomberSprites(int num_player, int dir, int action);
SDL_Rect getBlueSprites(int dir, int action);
SDL_Rect getBlackSprites(int dir, int action);
SDL_Rect getRedSprites(int dir, int action);
SDL_Rect getWhiteSprites(int dir, int action);
SDL_Rect getBombSprites(int type);
int	 getExplosionX(int index);
SDL_Rect getCenterExplosion(int type);
SDL_Rect getExplosionSprite(int x, int y, int width, int height);
SDL_Rect getExplosionSprites(int type);

/**
 * INIT
**/
void initSprites();
void initBomberSprites(int y);
void initBombSprites();
void initExplosionSprites();

#endif /* !_BOMBER_SPRITES_H_ */
